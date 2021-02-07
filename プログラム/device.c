#include "device.h"

#define SONAR_ALERT_DISTANCE 15

static int touch = 0;
static int color = 0;
static int type = 0;
static int reflect = 0;
static int ambient = 0;
static int sonor = 0;
static int gyro = 0;

static int l_angle = 0;
static int r_angle = 0;
static int arm_angle = 0;

rgb_raw_t rgb;

void change_LED_green()
{
    ev3_led_set_color(LED_GREEN); /* スタート通知 */
}

void change_LED_red()
{
     ev3_led_set_color(LED_RED); /* スタート通知 */
}

void device_init()
{
    /* センサー入力ポートの設定 */
    ev3_sensor_config(sonar_sensor, ULTRASONIC_SENSOR);
    ev3_sensor_config(color_sensor, COLOR_SENSOR);
    ev3_color_sensor_get_reflect(color_sensor); /* 反射率モード */
    ev3_sensor_config(touch_sensor, TOUCH_SENSOR);
    ev3_sensor_config(gyro_sensor, GYRO_SENSOR);
    /* モーター出力ポートの設定 */
    ev3_motor_config(left_motor, LARGE_MOTOR);
    ev3_motor_config(right_motor, LARGE_MOTOR);
    ev3_motor_config(arm_motor, LARGE_MOTOR);

    ev3_motor_reset_counts(arm_motor);
}

int get_touchsensor()
{
    touch = ev3_touch_sensor_is_pressed(touch_sensor);
    return touch;
}

int get_reflectsensor()
{
    reflect = ev3_color_sensor_get_reflect(color_sensor);
    return reflect;
}

int get_sonorsensor()
{
    sonor = ev3_ultrasonic_sensor_get_distance(sonar_sensor);
    return sonor;
}

int get_gyrosensor()
{
    gyro = ev3_gyro_sensor_get_rate(gyro_sensor);
    return gyro;
}

int get_ambientsensor()
{
    ambient = ev3_color_sensor_get_ambient(color_sensor);
    return ambient;
}

void encode_l_motor(int motorL)
{
    ev3_motor_set_power(left_motor,motorL);
}

void encode_r_motor(int motorR)
{
    ev3_motor_set_power(right_motor,motorR);
}

void encode_arm_motor(int motorArm)
{
    ev3_motor_set_power(arm_motor,motorArm);
}

int get_rgbsensor()
{   
    ev3_color_sensor_get_rgb_raw(color_sensor, &rgb);
    printf("RGB : %d, %d, %d 環境光 : %d 反射光 : %d\n",rgb.r, rgb.g, rgb.b, get_ambientsensor(), get_reflectsensor());
    color = (rgb.r + rgb.g + rgb.b)/3;
    return color;
}

void stop_wheel()
{
    ev3_motor_stop(left_motor,true);
    ev3_motor_stop(right_motor,true);
}

void stop_wheel_slowly()
{
    ev3_motor_stop(left_motor,false);
    ev3_motor_stop(right_motor,false);
}

int get_l_motor_ang()
{
    l_angle = ev3_motor_get_counts(left_motor);
    return l_angle;
}

int get_r_motor_ang()
{
    r_angle = ev3_motor_get_counts(right_motor);
    return r_angle;
}

int get_arm_motor_ang()
{
    int arm_angle = ev3_motor_get_counts(arm_motor) + 50;
    return arm_angle;
}

void stop_arm_motor()
{
    ev3_motor_stop(arm_motor,true);
}

void motor_reset()
{
    /* 走行モーターエンコーダーリセット */
    ev3_motor_reset_counts(left_motor);
    ev3_motor_reset_counts(right_motor);
}

/*青色を検知すると1を返し、できなかった場合0を返す関数*/
int detect_blue()
{
    int Red = 70;    //Redの閾値    白基準で設定中
    int Green = 90; //Greenの閾値
    int Blue = 100; //Blueの閾値
    int ambient = get_ambientsensor() -20;  //青線上の環境光の平均値が20

    ev3_color_sensor_get_rgb_raw(color_sensor, &rgb);   //rgb.rで赤,rgb.bで青の値を取る

    //printf("RGB : %d, %d, %d 環境光 : %d\n",rgb.r, rgb.g, rgb.b, ambient+20); //デバッグ用
    if((rgb.r -3.3*ambient)< Red  && (rgb.g -3.8*ambient)< Green && (rgb.b -5*ambient)> Blue)
    {
        //printf("青色を検知！ RGB : %d, %d, %d 環境光 : %d\n",rgb.r, rgb.g, rgb.b, ambient+20);
        return 1;
    }
    return 0;
}

/*赤ブロックを検知すると1を返し、できなかった場合0を返す関数*/
int detect_red_block()
{
    int Red = 65;    //Redの閾値    白基準で設定中
    int Green = 60; //Greenの閾値
    int Blue = 60; //Blueの閾値
    ev3_color_sensor_get_rgb_raw(color_sensor, &rgb);   //rgb.rで赤,rgb.bで青の値を取る
    printf("RGB : %d, %d, %d\n",rgb.r, rgb.g, rgb.b); //デバッグ用
    if(rgb.r > Red && rgb.g < Green && rgb.b < Blue)
    {
        printf("ブロックを検知！ RGB : %d, %d, %d\n",rgb.r, rgb.g, rgb.b);
        return 1;
    }
    return 0;
}

//*****************************************************************************
// 関数名 : sonar_alert
// 引数 : 無し
// 返り値 : 1(障害物あり)/0(障害物無し)
// 概要 : 超音波センサによる障害物検知
//*****************************************************************************
int sonar_alert(void)
{
    static unsigned int counter = 0;
    static int alert = 0;

    signed int distance;

    if (++counter == 40/4) /* 約40msec周期毎に障害物検知  */
    {
        /*
         * 超音波センサによる距離測定周期は、超音波の減衰特性に依存します。
         * NXTの場合は、40msec周期程度が経験上の最短測定周期です。
         * EV3の場合は、要確認
         */
        distance =  get_sonorsensor();
        if ((distance <= SONAR_ALERT_DISTANCE) && (distance >= 0))
        {
            alert = 1; /* 障害物を検知 */
        }
        else
        {
            alert = 0; /* 障害物無し */
        }
        counter = 0;
    }

    return alert;
}