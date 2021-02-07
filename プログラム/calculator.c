#include "calculator.h"
#include "stdio.h"
#define w 5.1 //走行体の幅(単位[mm])
#define enf 2.4 //総積算距離を演算するにあたっての補正係数
#define delta_t 0.004


static double total_L_dist = 0;//左輪のみの総積算距離　->コンパスに利用
static double total_R_dist = 0;//右輪のみの総積算距離  ->コンパスに利用
static int old_ang_L = 0;//ひとつ前の左輪の角度
static int old_ang_R = 0;//ひとつ前の右輪の角度
static double distance = 0;//各phaseでの総積算距離
static double distance_L = 0;
static double distance_R = 0;
static int total_distance = 0;//全体の総積算距離


static int diff[2] = {0};//差分を格納する配列
static int integral = 0;//積分初期値

static int change_angle_L = 0;   //左輪の角度変化値
static int change_angle_R = 0;   //右輪の角度変化値
static int  flag = 0;  //初回起動時の処理のため
//****************************************************************************************
// 関数名 : cal_turn
// 引数 　: int   light      - 輝度センサの値
//      　  int   threthold  - 閾値
//          double  KP       - Pゲイン(比例係数)
// 
// 返り値 : double  turndata　- 旋回量(今は比例制御しか実装していないため非常に単純。)
// 概要 　: 比例制御を用いて旋回量を計算する
// 追加   : 積分制御(I制御)　微分制御(D制御)
//****************************************************************************************
double cal_turn(int course,int light,int threthold,double KP,double KI)
{
    double turndata = 0;//旋回量

    diff[0] = diff[1];//値を後進する
    diff[1] = (threthold - light);//差分を格納する
    
    int p = KP * 5 * diff[1];//比例演算の旋回量
    int integral = integral +  ((diff[0] + diff[1]) /2.0) * delta_t;//積分演算を行う(台形公式)
    int i = KI * integral;//積分演算の旋回量

    turndata = course * (p + i);
    return turndata;
}

//****************************************************************************************
// 関数名 : cal_distance
// 引数 　: 無し
// 
// 返り値 : int  distance   -   各phaseでの総積算距離(phase終了毎にリセットされている前提)
// 概要 　: 各phaseでの総積算距離を求める。
//****************************************************************************************
int cal_distance()
{
 
    int now_ang_L = get_l_motor_ang();//今の左輪の角度
    int now_ang_R = get_r_motor_ang();//今の右輪の角度
    int d_count_L = now_ang_L - old_ang_L;//左輪の角度の差分
    int d_count_R = now_ang_R - old_ang_R;//右輪の角度の差分
    
    distance_L = 2*314*w*d_count_L/36000;//差分を下にした左輪の進んだ距離
    distance_R = 2*314*w*d_count_R/36000;//差分を下にした右輪の進んだ距離


    distance = distance + (distance_L + distance_R)/ 2;//総積算距離を更新
    old_ang_R = now_ang_R;//左輪の角度を更新
    old_ang_L = now_ang_L;//右輪の角度を更新
    total_L_dist = total_L_dist + distance_L;//左輪の総積算距離を更新
    total_R_dist = total_R_dist + distance_R;//右輪の総積算距離を更新

    //printf("%d\n",distance);
    return (int)distance;
}

//****************************************************************************************
// 関数名 : cal_distance
// 引数 　: 無し
// 
// 返り値 : double  distance   -   各phaseでの総積算距離(phase終了毎にリセットされている前提)
// 概要 　: 各phaseでの総積算距離を求める。
//****************************************************************************************
double fcal_distance()
{
 
    int now_ang_L = get_l_motor_ang();//今の左輪の角度
    int now_ang_R = get_r_motor_ang();//今の右輪の角度
    int d_count_L = now_ang_L - old_ang_L;//左輪の角度の差分
    int d_count_R = now_ang_R - old_ang_R;//右輪の角度の差分
    
    distance_L = 2*314*w*d_count_L/36000;//差分を下にした左輪の進んだ距離
    distance_R = 2*314*w*d_count_R/36000;//差分を下にした右輪の進んだ距離


    distance = distance + (distance_L + distance_R)/ 2;//総積算距離を更新
    old_ang_R = now_ang_R;//左輪の角度を更新
    old_ang_L = now_ang_L;//右輪の角度を更新
    total_L_dist = total_L_dist + distance_L;//左輪の総積算距離を更新
    total_R_dist = total_R_dist + distance_R;//右輪の総積算距離を更新

    //printf("%d\n",distance);
    return distance;
}




double get_L_distance()
{
    return total_L_dist;
}
//****************************************************************************************
// 関数名 : distance_reset
// 引数 　: 無し
// 
// 返り値 : 無し
// 概要 　: 各phaseでの総積算距離をリセットする
//****************************************************************************************
void distance_reset()
{
    total_distance = distance;
    total_L_dist = 0;
    total_R_dist = 0;
    distance = 0;
}



int arm_control(int goal_angle)
{
    int now_angle = get_arm_motor_ang();
    int diff = now_angle - goal_angle;
    encode_arm_motor(-(0.85 * diff));
    if((diff <= 1) && (diff >= -1)) 
    {
        stop_arm_motor();
        return 1;
    }
    return 0;
}

//****************************************************************************************
// 関数名 : do_angle_turning
// 引数 　: int threshold   -閾値(何度回転するか)
//              int direction   -0で右向き、0以外で左向き
//              unsigned int swing_speed    -回転速度
// 返り値 : 1(回転完了)/0(回転未完了))
// 概要 　: その場で回転をする
//****************************************************************************************
int do_angle_turning(int threshold, int direction, unsigned int swing_speed)
{
    static int base_angle_L,base_angle_R;

    int now_ang_L = get_l_motor_ang();//今の左輪の角度
    int now_ang_R = get_r_motor_ang();//今の右輪の角度
    int d_count_L = now_ang_L - old_ang_L;//左輪の角度の差分
    int d_count_R = now_ang_R - old_ang_R;//右輪の角度の差分
    
    change_angle_L += d_count_L;    //左輪の角度変化値の更新
    change_angle_R += d_count_R;    //右輪の角度変化値の更新
    old_ang_R = now_ang_R;  //左輪の角度を更新
    old_ang_L = now_ang_L;  //右輪の角度を更新

    /*初回だけ呼び出す処理*/
    if(flag == 0)
    {
        base_angle_L = change_angle_L;
        base_angle_R = change_angle_R;
        flag = 1;
    }
    //printf("            %d  %d\n",now_ang_L,now_ang_R);
    //printf("%d  %d      %d\n",change_angle_L,change_angle_R,base_angle_R);
    if(direction == 0)
    {
        encode_l_motor(swing_speed);
        encode_r_motor(-swing_speed);
       if(change_angle_L > base_angle_L + threshold)
        {
            encode_l_motor(0);
        }
        if(change_angle_R < base_angle_R - threshold)
        {
            encode_r_motor(0);
        }

        if((change_angle_L > base_angle_L + threshold) && (change_angle_R < base_angle_R - threshold))
        {
            flag = 0;
            return 1;
        }
    }
    else
    {
        encode_l_motor(-swing_speed);
        encode_r_motor(swing_speed);
        if(change_angle_L < base_angle_L - threshold)
        {
            encode_l_motor(0);
        }
        if(change_angle_R > base_angle_R + threshold)
        {
            encode_r_motor(0);
        }

        if((change_angle_L < base_angle_L - threshold) && (change_angle_R >  base_angle_R + threshold))
        {
            flag = 0;
            return 1;
        }
    }
    return 0;
}

//****************************************************************************************
// 関数名 : do_dancing_turn
// 引数 　: int threshold   -閾値(何度回転するか)
//              int direction   -0で右向き、0以外で左向き
//              unsigned int swing_speed    -回転速度
// 返り値 : 1(回転完了)/0(回転未完了))
// 概要 　: 片方の車輪を軸に回転をする
//****************************************************************************************
int do_dancing_turn(int threshold, int direction, int swing_speed)
{
    static int base_angle_L,base_angle_R;

    int now_ang_L = get_l_motor_ang();//今の左輪の角度
    int now_ang_R = get_r_motor_ang();//今の右輪の角度
    int d_count_L = now_ang_L - old_ang_L;//左輪の角度の差分
    int d_count_R = now_ang_R - old_ang_R;//右輪の角度の差分
    
    change_angle_L += d_count_L;    //左輪の角度変化値の更新
    change_angle_R += d_count_R;    //右輪の角度変化値の更新
    old_ang_R = now_ang_R;  //左輪の角度を更新
    old_ang_L = now_ang_L;  //右輪の角度を更新

    /*初回だけ呼び出す処理*/
    if(flag == 0)
    {
        base_angle_L = change_angle_L;
        base_angle_R = change_angle_R;
        flag = 1;
    }
    //printf("            %d  %d\n",now_ang_L,now_ang_R);
    //printf("%d  %d      %d\n",change_angle_L,change_angle_R,base_angle_R);
    if(direction == 0)
    {
        encode_l_motor(swing_speed);
        encode_r_motor(0);
       if(change_angle_L > base_angle_L + threshold)
        {
            encode_l_motor(0);
            flag = 0;
            return 1;
        }
    }
    else
    {
        encode_l_motor(0);
        encode_r_motor(swing_speed);
        if(change_angle_R > base_angle_R + threshold)
        {
            encode_r_motor(0);
            flag = 0;
            return 1;
        }
    }
    return 0;
}
