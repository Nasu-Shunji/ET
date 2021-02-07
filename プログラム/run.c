#include "run.h"
static int  flag = 0;  //初回起動時の処理のため
static int speed;
//****************************************************************************************
// 関数名 : run
// 引数 　: int   forward - エンコードにあたっての基準値(速さ)
//      　  double  turn  - 旋回量
// 
// 返り値 : 無し
// 概要 　: 各モータに対して旋回量を加算した出力を行う
//****************************************************************************************
void run(int forward,double turn)
{
    int motorL = forward + turn;//左輪出力値演算
    /*左輪限界値演算*/
    if(motorL >= 100)
    {
        motorL = 100;
    }
    else if(motorL <= -100)
    {
        motorL = -100;
    }

    int motorR = forward - turn;//右輪出力値演算
    /*右輪限界値演算*/
    if(motorR >= 100)
    {
        motorR = 100;
    }
    else if(motorR <= -100)
    {
        motorR = -100;
    }

    /*出力*/
    encode_l_motor(motorL);
    encode_r_motor(motorR);
}

void spin(int forward)
{
    encode_l_motor(forward);
    encode_r_motor(-forward);
}

void accel_run(int first_speed, int max_speed)
{
    static unsigned int counter = 0;
    int speed_difference = max_speed - first_speed;

    if(speed_difference == 0)
    {
        printf("Error : invalid_value");
        return;
    }

    /*初回のみ実行*/
    if(flag == 0)
    {
        speed = first_speed;
        flag = 1;
    }

    encode_l_motor(speed);
    encode_r_motor(speed);
    if (++counter == 15)
    {
        if(speed_difference > 0)
        {
            speed++;
            if(speed > max_speed)
            {
                speed = max_speed;
            }
        }
        else
        {
            speed--;
            if(speed < max_speed)
            {
                speed = max_speed;
            }
        }
        //printf("現在のスピード：%d\n",speed);
        encode_l_motor(speed);
        encode_r_motor(speed);
        counter = 0;
    }
}

void reset_accel_run()
{
    flag = 0;
}