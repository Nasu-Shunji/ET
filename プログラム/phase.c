#include "phase.h"
#include "stdio.h"

static int course = 0;
static int timer = 0;
static int pattern = 0;
static int status_phase5 = 0;
static int status_phase14 = 0;
static int status_phase19 = 0;
static int status_phase22 = 0;
static int status_phase23 = 0;
static int status_phase24 = 0;
static int status_phase26 = 0;
static int data_dist_btw_C = 0;
static int data_dist_btw_D = 0;


void set_course(int course_key)
{
    course = course_key;
}


//****************************************************************************************
// 関数名 : select_spd_phase
// 引数 　: int   select_spd_phase_key - 現在のスピード競技phase
// 
// 返り値 : int   spd_phase_key        - 次のスピード競技phase
// 概要 　: 次行うべきスピード競技phaseの決定を行う。各スピード競技phaseが終了次第呼び出す。
//          呼び出すたびにスピード競技phaseが一つずつ遷移する
// 追加   : (例外処理:引数が配列サイズよりも大きいときの処理)
//****************************************************************************************
int select_spd_phase(int select_spd_phase_key)
{
    enum SPD_PHASE_NUM SPN[] = {    PHASE1,
                                    PHASE2,
                                    PHASE3,
                                    PHASE4,
                                    PHASE5,
                                    PHASE6,
                                    PHASE7,
                                    PHASE8,
                                    PHASE9,
                                    PHASE10,
                                    PHASE11,
                                    PHASE12,
                                    PHASE13,
                                    PHASE14,
                                    PHASE15,
                                    PHASE16,
                                    PHASE17
                                };
    int spd_phase_key = SPN[select_spd_phase_key];
    if(select_spd_phase_key % 2 == 0)
    {
        change_LED_green();
    }
    else
    {
        change_LED_red();
    }
    return spd_phase_key;
}


//****************************************************************************************
// 関数名 : select_dif_phase
// 引数 　: int   select_dif_phase_key - 現在のスピード競技phase
// 
// 返り値 : int   dif_phase_key        - 次のスピード競技phase
// 概要 　: 次行うべきdifphaseの決定を行う。各difphaseが終了次第呼び出す。
//          呼び出すたびにdifphaseが一つずつ遷移する
// 追加   : (例外処理:引数が配列サイズよりも大きいときの処理)
//****************************************************************************************
int select_dif_phase(int select_dif_phase_key)
{
    enum DIF_PHASE_NUM DPN[] = {    D_PHASE1,
                                    D_PHASE2,
                                    D_PHASE3,
                                    D_PHASE4,
                                    D_PHASE5,
                                    D_PHASE6,
                                    D_PHASE7,
                                    D_PHASE8,
                                    D_PHASE9,
                                    D_PHASE10,
                                    D_PHASE11,
                                    D_PHASE12,
                                    D_PHASE13,
                                    D_PHASE14,
                                    D_PHASE15,
                                    D_PHASE16,
                                    D_PHASE17,
                                    D_PHASE18,
                                    D_PHASE19,
                                    D_PHASE20,
                                    D_PHASE21,
                                    D_PHASE22,
                                    D_PHASE23,
                                    D_PHASE24,
                                    D_PHASE25,
                                    D_PHASE26,
                                    D_PHASE27,
                                    D_PHASE28,
                                    D_PHASE29,
                                    D_PHASE30,
                                    D_PHASE31,
                                    D_PHASE32,
                                    D_PHASE33,
                                    D_PHASE34,
                                    D_PHASE35,
                                    D_PHASE36,
                                    D_PHASE37,
                                    D_PHASE38,
                                    D_PHASE39,
                                    D_PHASE40
                                };
    int dif_phase_key = DPN[select_dif_phase_key];
    printf("phase:%d\n",dif_phase_key);
    if(select_dif_phase_key % 2 == 0)
    {
        change_LED_green();
    }
    else
    {
        change_LED_red();
    }
    return dif_phase_key;
}

//****************************************************************************************
// 関数名 : select_gir_phase
// 引数 　: int   select_gir_phase_key - 現在のガレージphase
// 
// 返り値 : int   gir_phase_key        - 次のガレージphase
// 概要 　: 次行うべきガレージphaseの決定を行う。各ガレージphaseが終了次第呼び出す。
//          呼び出すたびにガレージphaseが一つずつ遷移する
// 追加   : (例外処理:引数が配列サイズよりも大きいときの処理)
//****************************************************************************************
int select_gir_phase(int select_gir_phase_key)
{
    enum GIR_PHASE_NUM GIN[] = {    G_PHASE1,
                                    G_PHASE2,
                                    G_PHASE3,
                                    G_PHASE4,
                                    G_PHASE5,
                                    G_PHASE6,
                                    G_PHASE7,
                                    G_PHASE8,
                                    G_PHASE9,
                                    G_PHASE10
                                };
    int gir_phase_key = GIN[select_gir_phase_key];
    if(select_gir_phase_key % 2 == 0)
    {
        change_LED_green();
    }
    else
    {
        change_LED_red();
    }
    return gir_phase_key;
}


//****************************************************************************************
// 関数名 : act_spd_phase1
// 引数 　: int   threthold - 閾値
// 
// 返り値 : END_PHASE or 0  - phase内容完了通知
// 概要 　: スピード競技エリアphase1の内容を行う。
//          目的は初めの直線の攻略。
//          スピード:80     走行距離:110
// 作成者 :　大橋　
//****************************************************************************************
int act_spd_phase1(int threthold)
{
    int light = get_reflectsensor();
    int distance = cal_distance();
    double turn = cal_turn(course,light,threthold,0.30,0);
    run(60,turn);
    if(distance > 95)
    {
        distance_reset();
        return END_PHASE;
    }
    return 0;
}


//****************************************************************************************
// 関数名 : act_spd_phase2
// 引数 　: int   threthold - 閾値
// 
// 返り値 : END_PHASE or 0  - phase内容完了通知
// 概要 　: スピード競技エリアphase2の内容を行う。
//          目的はphase1後のカーブの攻略。
//          スピード:100     走行距離:150
// 作成者 :　大橋　
//****************************************************************************************
int act_spd_phase2(int threthold)
{
    int light = get_reflectsensor();
    int distance = cal_distance();
    double turn = cal_turn(course,light,threthold,0.40,0);
    run(50,turn);
    if(distance > 115)
    {
        distance_reset();
        return END_PHASE;
    }
    return 0;
}

//****************************************************************************************
// 関数名 : act_spd_phase3
// 引数 　: int   threthold - 閾値
// 
// 返り値 : END_PHASE or 0  - phase内容完了通知
// 概要 　: スピード競技エリアphase3の内容を行う。
//          目的はphase2後の直線の攻略。
//          スピード:70     走行距離:
// 作成者 :　大橋　
//****************************************************************************************
int act_spd_phase3(int threthold)
{

    int light = get_reflectsensor();
    int distance = cal_distance();
    double turn = cal_turn(course,light,threthold,0.34,0);
    run(60,turn);
    if(distance > 42)
    {
        distance_reset();
        return END_PHASE;
    }
    return 0;
}

//****************************************************************************************
// 関数名 : act_spd_phase4
// 引数 　: int   threthold - 閾値
// 
// 返り値 : END_PHASE or 0  - phase内容完了通知
// 概要 　: スピード競技エリアphase4の内容を行う。
//          目的はphase3後のカーブの攻略。
//          スピード:70     走行距離:80
// 作成者 :　大橋　
//****************************************************************************************
int act_spd_phase4(int threthold)
{
    int light = get_reflectsensor();
    int distance = cal_distance();
    double turn = cal_turn(course,light,threthold,0.40,0.001);
    run(50,turn);
    if(distance > 126)
    {
        distance_reset();
        return END_PHASE;
    }
    return 0;
}

//****************************************************************************************
// 関数名 : act_spd_phase5
// 引数 　: int   threthold - 閾値
// 
// 返り値 : END_PHASE or 0  - phase内容完了通知
// 概要 　: スピード競技エリアphase5の内容を行う。
//          目的はphase4後の直線の攻略。
//          スピード:90     走行距離:100
// 作成者 :　大橋　
//****************************************************************************************
int act_spd_phase5(int threthold)
{
    int light = get_reflectsensor();
    int distance = cal_distance();
    double turn = cal_turn(course,light,threthold+3,0.35,0.001);
    run(95,turn);
    if(distance > 61)
    {
        distance_reset();
        return END_PHASE;
    }
    return 0;
}

//****************************************************************************************
// 関数名 : act_spd_phase6
// 引数 　: int   threthold - 閾値
// 
// 返り値 : END_PHASE or 0  - phase内容完了通知
// 概要 　: スピード競技エリアphase6の内容を行う。
//          目的はphase5後のカーブの攻略。
//          スピード:70     走行距離:100
// 作成者 :　大橋　
//****************************************************************************************
int act_spd_phase6(int threthold)
{
    int light = get_reflectsensor();
    int distance = cal_distance();
    double turn = cal_turn(course,light,threthold+7,0.53,0.001);
    run(50,turn);
    if(distance > 52)
    {
        distance_reset();
        return END_PHASE;
    }
    return 0;
}

//****************************************************************************************
// 関数名 : act_spd_phase7
// 引数 　: int   threthold - 閾値
// 
// 返り値 : END_PHASE or 0  - phase内容完了通知
// 概要 　: スピード競技エリアphase7の内容を行う。
//          目的はphase6後の直線の攻略。
//          スピード:70     走行距離:100
// 作成者 :　大橋　
//****************************************************************************************
int act_spd_phase7(int threthold)
{
    int light = get_reflectsensor();
    int distance = cal_distance();
    double turn = cal_turn(course,light,threthold,0.40,0.001);
    run(70,turn);
    if(distance > 68)
    {
        distance_reset();
        return END_PHASE;
    }
    return 0;
}

//****************************************************************************************
// 関数名 : act_spd_phase8
// 引数 　: int   threthold - 閾値
// 
// 返り値 : END_PHASE or 0  - phase内容完了通知
// 概要 　: スピード競技エリアphase8の内容を行う。
//          目的はphase7後のカーブの攻略。
//          スピード:70     走行距離:100
// 作成者 :　大橋　
//****************************************************************************************
int act_spd_phase8(int threthold)
{
    int light = get_reflectsensor();
    int distance = cal_distance();
    double turn = cal_turn(course,light,threthold-5,0.38,0);
    run(60,turn);
    if(distance > 87)
    {
        distance_reset();
        return END_PHASE;
    }
    return 0;
}

//****************************************************************************************
// 関数名 : act_spd_phase9
// 引数 　: int   threthold - 閾値
// 
// 返り値 : END_PHASE or 0  - phase内容完了通知
// 概要 　: スピード競技エリアphase9の内容を行う。
//          目的はphase8後の直線の攻略。
//          スピード:70     走行距離:100
// 作成者 :　大橋　
//****************************************************************************************
int act_spd_phase9(int threthold)
{
    int light = get_reflectsensor();
    int distance = cal_distance();
    double turn = cal_turn(course,light,threthold-2,0.38,0);
    run(66,turn);
    if(distance > 80)
    {
        distance_reset();
        return END_PHASE;
    }
    return 0;
}

//****************************************************************************************
// 関数名 : act_spd_phase10
// 引数 　: int   threthold - 閾値
// 
// 返り値 : END_PHASE or 0  - phase内容完了通知
// 概要 　: スピード競技エリアphase10の内容を行う。
//          目的はphase9後のカーブの攻略。
//          スピード:70     走行距離:100
// 作成者 :　大橋　
//****************************************************************************************
int act_spd_phase10(int threthold)
{
    int light = get_reflectsensor();
    int distance = cal_distance();
    double turn = cal_turn(course,light,threthold,0.38,0.01);
    run(50,turn);
    if(distance > 60)
    {
        distance_reset();
        return END_PHASE;
    }
    return 0;
}

//****************************************************************************************
// 関数名 : act_spd_phase11
// 引数 　: int   threthold - 閾値
// 
// 返り値 : END_PHASE or 0  - phase内容完了通知
// 概要 　: スピード競技エリアphase11の内容を行う。
//          目的はphase10後の直線の攻略。
//          スピード:70     走行距離:100
// 作成者 :　大橋　
//****************************************************************************************
int act_spd_phase11(int threthold)
{
    int light = get_reflectsensor();
    int distance = cal_distance();
    double turn = cal_turn(course,light,threthold,0.38,0);
    run(60,turn);
    if(distance > 70)
    {
        distance_reset();
        return END_PHASE;
    }
    return 0;
}

//****************************************************************************************
// 関数名 : act_spd_phase12
// 引数 　: int   threthold - 閾値
// 
// 返り値 : END_PHASE or 0  - phase内容完了通知
// 概要 　: スピード競技エリアphase12の内容を行う。
//          目的はphase11後のカーブの攻略。
//          スピード:70     走行距離:100
// 作成者 :　大橋　
//****************************************************************************************
int act_spd_phase12(int threthold)
{
    int light = get_reflectsensor();
    int distance = cal_distance();
    double turn = cal_turn(course,light,threthold,0.40,0);
    run(30,turn);
    if(distance > 25)
    {
        distance_reset();
        return END_PHASE;
    }
    return 0;
}

//****************************************************************************************
// 関数名 : act_spd_phase13
// 引数 　: int   threthold - 閾値
// 
// 返り値 : END_PHASE or 0  - phase内容完了通知
// 概要 　: スピード競技エリアphase13の内容を行う。
//          目的はphase12後の直線の攻略。
//          スピード:70     走行距離:100
// 作成者 :　大橋　
//****************************************************************************************
int act_spd_phase13(int threthold)
{
    int light = get_reflectsensor();
    int distance = cal_distance();
    double turn = cal_turn(course,light,threthold,0.38,0.0);
    run(100,turn);
    if(distance > 125)
    {
        distance_reset();
        return END_PHASE;
    }
    return 0;
}


//****************************************************************************************
// 関数名 : act_spd_phase14
// 引数 　: int   threthold - 閾値
// 
// 返り値 : END_PHASE or 0  - phase内容完了通知
// 概要 　: スピード競技エリアphase13の内容を行う。
//          目的はphase12後の直線の攻略。
//          スピード:70     走行距離:100
// 作成者 :　大橋　
//****************************************************************************************
int act_spd_phase14(int threthold)
{
    int light = get_reflectsensor();
    int distance = cal_distance();
    double turn = cal_turn(course,light,threthold,0.40,0);
    run(42,turn);
    if(distance > 87)
    {
        distance_reset();
        return END_PHASE;
    }
    return 0;
}

//****************************************************************************************
// 関数名 : act_spd_phase15
// 引数 　: int   threthold - 閾値
// 
// 返り値 : END_PHASE or 0  - phase内容完了通知
// 概要 　: スピード競技エリアphase13の内容を行う。
//          目的はphase12後の直線の攻略。
//          スピード:70     走行距離:100
// 作成者 :　大橋　
//****************************************************************************************
int act_spd_phase15(int threthold)
{
    int light = get_reflectsensor();
    int distance = cal_distance();
    double turn = cal_turn(course,light+1,threthold,0.33,0.001);
    run(95,turn);
    if(distance > 80)
    {
        distance_reset();
        return END_PHASE;
    }
    return 0;
}

//****************************************************************************************
// 関数名 : act_spd_phase16
// 引数 　: int   threthold - 閾値
// 
// 返り値 : END_PHASE or 0  - phase内容完了通知
// 概要 　: スピード競技エリアphase13の内容を行う。
//          目的はphase12後の直線の攻略。
//          スピード:70     走行距離:100
// 作成者 :　大橋　
//****************************************************************************************
int act_spd_phase16(int threthold)
{
    int light = get_reflectsensor();
    int distance = cal_distance();
    double turn = cal_turn(course,light-4,threthold,0.50,0.001);
    run(43,turn);
    if(distance > 130)
    {
        distance_reset();
        return END_PHASE;
    }
    return 0;
}


//****************************************************************************************
// 関数名 : act_spd_phase16
// 引数 　: int   threthold - 閾値
// 
// 返り値 : END_PHASE or 0  - phase内容完了通知
// 概要 　: スピード競技エリアphase13の内容を行う。
//          目的はphase12後の直線の攻略。
//          スピード:70     走行距離:100
// 作成者 :　大橋　
//****************************************************************************************
int act_spd_phase17(int threthold)
{
    int light = get_reflectsensor();
    int distance = cal_distance();
    double turn = cal_turn(course,light,threthold,0.30,0.1);
    run(40,turn);
    if(distance > 20)
    {
        distance_reset();
        return END_PHASE;
    }
    return 0;
}

















//以下、難所スラロームプログラム


//phase1:腕を上げる(角度:20度)
int act_dif_phase1(int threthold)
{
    stop_wheel();
    arm_control(20);
    int now_arm_angle = get_arm_motor_ang();
    if(now_arm_angle > 15)
    {
        distance_reset();
        return END_PHASE;
    }
    return 0;
}

//phase2:右輪,左輪　それぞれエンコードする(板を上る)
int act_dif_phase2(int threthold)
{
    static int min_gyro = 0;
    int distance = cal_distance();
    int now_gyro = get_gyrosensor();
    if(course == 1)
    {
        encode_l_motor(38);
        encode_r_motor(37);
        if(now_gyro < min_gyro)
        {
            min_gyro = now_gyro;
        }
        if((distance > 42))
        {
            distance_reset();
            return END_PHASE;
        }
    }
    else
    {
        encode_r_motor(38);
        encode_l_motor(37);
        if(now_gyro < min_gyro)
        {
            min_gyro = now_gyro;
        }
        if((distance > 42))
        {
            distance_reset();
            return END_PHASE;
        }
    }
    return 0;
}

//phase3:腕を下の角度に戻す(基本的に停止する)
int act_dif_phase3(int threthold)
{
    arm_control(0);
    timer = timer + 1;
    stop_wheel();
    int distance = cal_distance();
    if(timer > 100)
    {
        distance_reset();
        timer = 0;
        return END_PHASE;
    }
    return 0;
}

//phase4:障害物Aを探索する。
int act_dif_phase4(int threthold)
{
    arm_control(0);
    static int status_dif3 = 0;
    int light = get_reflectsensor();
    int distance = cal_distance();
    int dist_btw_A = get_sonorsensor();
    //状態1 -> 大きく首を振り、Aを探索する
    if(course == 1)
    {
        if(status_dif3 == 0)
        {
            if(light > 13)
            {
                encode_r_motor(48);
                encode_l_motor(-5);
            }
            else
            {
                encode_l_motor(48);
                encode_r_motor(-5);
            }
            if(dist_btw_A < 20)
            {
                distance_reset();
                status_dif3 = 1;
            }
        }
        //状態2 -> 小さくLT走行することにより、体制を整える。
        else if(status_dif3 == 1)
        {
            if(light > 13)
            {
                encode_r_motor(23);
                encode_l_motor(5);
            }
            else
            {
                encode_l_motor(23);
                encode_r_motor(5);
            }
            if(distance > 8)
            {
                distance_reset();
                return END_PHASE;
            }
        }
    }
    else
    {
        if(status_dif3 == 0)
        {
            if(light > 13)
            {
                encode_l_motor(48);
                encode_r_motor(-5);
            }
            else
            {
                encode_r_motor(48);
                encode_l_motor(-5);
            }
            if(dist_btw_A < 20)
            {
                distance_reset();
                status_dif3 = 1;
            }
        }
        //状態2 -> 小さくLT走行することにより、体制を整える。
        else if(status_dif3 == 1)
        {
            if(light > 13)
            {
                encode_l_motor(23);
                encode_r_motor(5);
            }
            else
            {
                encode_r_motor(23);
                encode_l_motor(5);
            }
            if(distance > 8)
            {
                distance_reset();
                return END_PHASE;
            }
        }
    }
    return 0;
}

//phase5:停止する
int act_dif_phase5(int threthold)
{
    arm_control(0);
    timer = timer + 1;
    stop_wheel();
    int distance = cal_distance();
    if(timer > 20)
    {
        distance_reset();
        timer = 0;
        return END_PHASE;
    }
    return 0;
}

//phase6:45度回転する
int act_dif_phase6(int threthold)
{
    arm_control(0);
    if(course == 1)
    {
        spin(-23);
        double distance = fcal_distance();
        double distL = get_L_distance();
        if(distL < -4.90)
        {
            distance_reset();
            return END_PHASE;
        }
    }
    else
    {
        spin(23);
        double distance = fcal_distance();
        double distL = get_L_distance();
        if(distL > 4.90)
        {
            distance_reset();
            return END_PHASE;
        }
    }
    return 0;
}

//phase7:停止する
int act_dif_phase7(int threthold)
{
    arm_control(0);
    timer = timer + 1;
    stop_wheel();
    int distance = cal_distance();
    if(timer > 30)
    {
        distance_reset();
        timer = 0;
        return END_PHASE;
    }
    return 0;
}

//phase8:非LT走行し、少々進む
int act_dif_phase8(int threthold)
{
    double distance = fcal_distance();
    encode_l_motor(33);
    encode_r_motor(33);
    if(distance > 12.00)
    {
        distance_reset();
        return END_PHASE;
    }
    return 0;
}

//phase9:停止する
int act_dif_phase9(int threthold)
{
    arm_control(0);
    timer = timer + 1;
    stop_wheel();
    int distance = cal_distance();
    if(timer > 100)
    {
        distance_reset();
        timer = 0;
        return END_PHASE;
    }
    return 0;
}

//phase10:45度回転する
int act_dif_phase10(int threthold)
{
    arm_control(0);
    if(course == 1)
    {
        spin(10);
        double distance = fcal_distance();
        double distL = get_L_distance();
        if(distL > 4.78)
        {
            distance_reset();
            return END_PHASE;
        }
    }
    else
    {
        spin(-10);
        double distance = fcal_distance();
        double distL = get_L_distance();
        if(distL < -4.78)
        {
            distance_reset();
            return END_PHASE;
        }
    }
    return 0;
}

//phase11:停止する
int act_dif_phase11(int threthold)
{
    arm_control(0);
    timer = timer + 1;
    stop_wheel();
    int distance = cal_distance();
    if(timer > 50)
    {
        distance_reset();
        timer = 0;
        return END_PHASE;
    }
    return 0;
}


//phase12:超音波センサで障害物Bを補足する走行を行う。
int act_dif_phase12(int threthold)
{
    arm_control(0);
    int light = get_reflectsensor();
    double distance = fcal_distance();
    int dist_btw_B = get_sonorsensor();
    if(course == 1)
    {
        if(distance < 18.30)
        {
            encode_r_motor(18);
            encode_l_motor(17);
            if(dist_btw_B < 6)
            {
                distance_reset();
                return END_PHASE;
            }
        }
        else
        {
            if(dist_btw_B > 15)
            {
                encode_r_motor(20);
                encode_l_motor(0);
            }
            else
            {
                encode_l_motor(20);
                encode_r_motor(13);
            }
            if(dist_btw_B < 6)
            {
                distance_reset();
                return END_PHASE;
            }
        }
    }
    else
    {
        if(distance < 18.30)
        {
            encode_l_motor(18);
            encode_r_motor(17);
            if(dist_btw_B < 6)
            {
                distance_reset();
                return END_PHASE;
            }
        }
        else
        {
            if(dist_btw_B > 15)
            {
                encode_l_motor(20);
                encode_r_motor(0);
            }
            else
            {
                encode_r_motor(20);
                encode_l_motor(13);
            }
            if(dist_btw_B < 6)
            {
                distance_reset();
                return END_PHASE;
            }
        }
    }
    return 0;
}

//phase13:停止する
int act_dif_phase13(int threthold)
{
    arm_control(0);
    timer = timer + 1;
    stop_wheel();
    int distance = cal_distance();
    if(timer > 50)
    {
        distance_reset();
        timer = 0;
        return END_PHASE;
    }
    return 0;
}

//phase14:回転する(障害物B -> 障害物Cを補足する)
int act_dif_phase14(int threthold)
{
    arm_control(0);
    double distance = fcal_distance();
    double distL = get_L_distance();
    int dist_btw_B = get_sonorsensor();
    //printf("%d\n",dist_btw_B);
    if(course == 1)
    {
        if(status_phase14 == 0)
        {
            spin(6);
            if((dist_btw_B > 20) && (distL > 1.30))
            {
                distance_reset();
                return END_PHASE;
            }
        }
    }
    else
    {
        if(status_phase14 == 0)
        {
            spin(-6);
            if((dist_btw_B > 20) && (distL < -1.30))
            {
                distance_reset();
                return END_PHASE;
            }
        }
    }
    return 0;
}

//phase15:非LT走行で少し前進する
int act_dif_phase15(int threthold)
{
    arm_control(0);
    int distance = cal_distance();
    int dist_btw_C = get_sonorsensor();
    if(course == 1)
    {
        encode_l_motor(10);
        encode_r_motor(12);
        if((distance > 4.00))
        {
            distance_reset();
            return END_PHASE;
        }
    }
    else
    {
        encode_r_motor(10);
        encode_l_motor(12);
        if((distance > 4.00))
        {
            distance_reset();
            return END_PHASE;
        }
    }
    return 0;
}

//phase16:距離を測るだけ
int act_dif_phase16(int threthold)
{
    int dist_btw_C = get_sonorsensor();
    double distance = fcal_distance();
    double distL = get_L_distance();
    if(dist_btw_C > 40)
    {
        data_dist_btw_C = 2;//障害物から外れているパターン
    }
    else
    {
        data_dist_btw_C = 2;//障害物を補足しているパターン
    }
    return END_PHASE;
}

//phase17:phase16の結果に従って、走行方法を決める。
int act_dif_phase17(int threthold)
{
    int dist_btw_C = get_sonorsensor();
    double distance = fcal_distance();
    double distL = get_L_distance();
    //printf("%d\n",dist_btw_C);
    if(course == 1)
    {
        if(data_dist_btw_C == 1)
        {
            //障害物から外れている -> 前進する
            encode_l_motor(14);
            encode_r_motor(15);
            if((dist_btw_C < 10) || (distance > 15.5))
            {
                distance_reset();
                return END_PHASE;
            }
        }
        //障害物から外れるまで回転　-> 移動を繰り返す
        else
        {
            //障害物から外れていない -> 回転し、外してから前進する。
            static int status_phase14 = 0;
            //回転する
            if(status_phase14 == 0)
            {
                spin(10);
                if((distL > 3.5))
                {
                    status_phase14 = 1;
                    distance_reset();
                }
            }
            //障害物から外れているため、前進する
            else if(status_phase14 == 1)
            {
                //障害物から外れている -> 前進する
                encode_l_motor(19);
                encode_r_motor(28);
                if((dist_btw_C < 10) || (distance > 16.5))
                {
                    distance_reset();
                    return END_PHASE;
                }
            }
        }
    }
    else
    {
        if(data_dist_btw_C == 1)
        {
            //障害物から外れている -> 前進する
            encode_r_motor(14);
            encode_l_motor(15);
            if((dist_btw_C < 10) || (distance > 15.5))
            {
                distance_reset();
                return END_PHASE;
            }
        }
        //障害物から外れるまで回転　-> 移動を繰り返す
        else
        {
            //障害物から外れていない -> 回転し、外してから前進する。
            static int status_phase14 = 0;
            //回転する
            if(status_phase14 == 0)
            {
                spin(-10);
                if((distL < -3.5))
                {
                    status_phase14 = 1;
                    distance_reset();
                }
            }
            //障害物から外れているため、前進する
            else if(status_phase14 == 1)
            {
                //障害物から外れている -> 前進する
                encode_r_motor(19);
                encode_l_motor(28);
                if((dist_btw_C < 10) || (distance > 16.5))
                {
                    distance_reset();
                    return END_PHASE;
                }
            }
        }
    }
    return 0;
}



//phase18:LT走行する
int act_dif_phase18(int threthold)
{
    arm_control(9);
    int light = get_reflectsensor();
    int distance = cal_distance();
    int dist_btw_C = get_sonorsensor();
    //printf("%d:%d\n",dist_btw_C,distance);
    if(course == 1)
    {
        if(light > 18)
        {
            encode_r_motor(10);
            encode_l_motor(-4);
        }
        else
        {
            encode_l_motor(10);
            encode_r_motor(-4);
        }
        if((dist_btw_C < 23) && (distance > 7))
        {
            distance_reset();
            return END_PHASE;
        }
    }
    else
    {
        if(light > 18)
        {
            encode_l_motor(10);
            encode_r_motor(-4);
        }
        else
        {
            encode_r_motor(10);
            encode_l_motor(-4);
        }
        if((dist_btw_C < 23) && (distance > 7))
        {
            distance_reset();
            return END_PHASE;
        }
    }
    return 0;
}

//phase19:回転して障害物から外れる
int act_dif_phase19(int threthold)
{
    arm_control(0);
    if(course == 1)
    {
        spin(-3);
        double distance = fcal_distance();
        double distL = get_L_distance();
        int dist_btw_D = get_sonorsensor();
        if(dist_btw_D > 200)
        {
            distance_reset();
            return END_PHASE;
        }
    }
    else
    {
        spin(3);
        double distance = fcal_distance();
        double distL = get_L_distance();
        int dist_btw_D = get_sonorsensor();
        if(dist_btw_D > 200)
        {
            distance_reset();
            return END_PHASE;
        }
    }
    return 0;
}

//phase20:停止する
int act_dif_phase20(int threthold)
{
    arm_control(0);
    timer = timer + 1;
    stop_wheel();
    int distance = cal_distance();
    int light = get_reflectsensor();
    int dist_btw_C = get_sonorsensor();
    //printf("light = %d : dist = %d\n",light,dist_btw_C);
    //printf("%d\n",dist_btw_C);
    if(timer > 100)
    {
        distance_reset();
        timer = 0;
        return END_PHASE;
    }
    return 0;
}

//phase19:非LT走行で走行する
int act_dif_phase21(int threthold)
{
    int dist_btw_C = get_sonorsensor();
    double distance = fcal_distance();
    double distL = get_L_distance();
    if(course == 1)
    {
        encode_l_motor(0);
        encode_r_motor(7);
        if(distance > 2.95)
        {
            distance_reset();
            return END_PHASE;
        }
    }
    else
    {
        encode_r_motor(0);
        encode_l_motor(7);
        if(distance > 2.95)
        {
            distance_reset();
            return END_PHASE;
        }
    }
    return 0;
}

//phase20:非LT走行で曲線走行する
int act_dif_phase22(int threthold)
{
    int dist_btw_D = get_sonorsensor();
    double distance = fcal_distance();
    double distL = get_L_distance();
    static int status_phase20 = 0;
    if(course == 1)
    {
        //2発目
        if(status_phase20 == 0)
        {
            encode_l_motor(5);
            encode_r_motor(0);
            if(distance > 2.80)
            {
                distance_reset();
                status_phase20 = 1;
            }
        }
        //3発目
        else if(status_phase20 == 1)
        {
            encode_l_motor(0);
            encode_r_motor(5);
            if(distance > 3.35)
            {
                distance_reset();
                status_phase20 = 2;
            }
        }
        //4発目　->　ここから多少早くてもOK!!
        else if(status_phase20 == 2)
        {
            encode_l_motor(18);
            encode_r_motor(6);
            if(distance > 9.15)
            {
                distance_reset();
                status_phase20 = 3;
            }
        }
        //もう一くだり追加する。
        else if(status_phase20 == 3)
        {
            encode_l_motor(12);
            encode_r_motor(20);
            if(distance > 3.25)
            {
                distance_reset();
                status_phase20 = 4;
            }
        }
        else if(status_phase20 == 4)
        {
            encode_l_motor(7);
            encode_r_motor(-3);
            if(distance > 1.00)
            {
                distance_reset();
                return END_PHASE;
            }
        }
    }
    else
    {
        //2発目
        if(status_phase20 == 0)
        {
            encode_r_motor(5);
            encode_l_motor(0);
            if(distance > 2.80)
            {
                distance_reset();
                status_phase20 = 1;
            }
        }
        //3発目
        else if(status_phase20 == 1)
        {
            encode_r_motor(0);
            encode_l_motor(5);
            if(distance > 3.35)
            {
                distance_reset();
                status_phase20 = 2;
            }
        }
        //4発目　->　ここから多少早くてもOK!!
        else if(status_phase20 == 2)
        {
            encode_r_motor(18);
            encode_l_motor(6);
            if(distance > 9.15)
            {
                distance_reset();
                status_phase20 = 3;
            }
        }
        //もう一くだり追加する。
        else if(status_phase20 == 3)
        {
            encode_r_motor(12);
            encode_l_motor(20);
            if(distance > 3.25)
            {
                distance_reset();
                status_phase20 = 4;
            }
        }
        else if(status_phase20 == 4)
        {
            encode_r_motor(7);
            encode_l_motor(-3);
            if(distance > 1.00)
            {
                distance_reset();
                return END_PHASE;
            }
        }
    }
    return 0;
}

int act_dif_phase23(int threthold)
{
    arm_control(0);
    int light = get_reflectsensor();
    int distance = cal_distance();
    int dist_btw_B = get_sonorsensor();
    if(course == 1)
    {
        if(status_phase23 == 0)
        {
            timer = timer + 1;
            stop_wheel();
            //printf("light = %d : dist = %d\n",light,dist_btw_C);
            //printf("%d\n",dist_btw_C);
            if(timer > 20)
            {
                distance_reset();
                timer = 0;
                status_phase23 = 1;
            }
        }
        else if(status_phase23 == 1)
        {
            //printf("%d\n",dist_btw_B);
            if(dist_btw_B < 20)
            {
                encode_r_motor(13);
                encode_l_motor(-2);
            }
            else
            {
                encode_l_motor(13);
                encode_r_motor(0);
            }
            if(dist_btw_B < 10)
            {
                if(dist_btw_B < 10)
                {
                    status_phase22 =  0;
                }
                distance_reset();
                return END_PHASE;
            }
        }
    }
    else
    {
        if(status_phase23 == 0)
        {
            timer = timer + 1;
            stop_wheel();
            //printf("light = %d : dist = %d\n",light,dist_btw_C);
            //printf("%d\n",dist_btw_C);
            if(timer > 20)
            {
                distance_reset();
                timer = 0;
                status_phase23 = 1;
            }
        }
        else if(status_phase23 == 1)
        {
            printf("%d\n",dist_btw_B);
            if(dist_btw_B < 20)
            {
                encode_l_motor(13);
                encode_r_motor(-2);
            }
            else
            {
                encode_r_motor(13);
                encode_l_motor(0);
            }
            if(dist_btw_B < 10)
            {
                if(dist_btw_B < 10)
                {
                    status_phase22 =  0;
                }
                distance_reset();
                return END_PHASE;
            }
        }
    }
    return 0;
}

int act_dif_phase24(int threthold)
{
    arm_control(0);
    int distance = cal_distance();
    int light = get_reflectsensor();
    int dist_btw_C = get_sonorsensor();
    if(status_phase22 == 1)
    {
            encode_l_motor(-4);
            encode_r_motor(-4);
            if(dist_btw_C > 5)
            {
                return END_PHASE;
                distance_reset();
            }
    }
    else if(status_phase22 == 0)
    {
        timer = timer + 1;
        stop_wheel();
        //printf("light = %d : dist = %d\n",light,dist_btw_C);
        //printf("%d\n",dist_btw_C);
        if(timer > 50)
        {
            distance_reset();
            timer = 0;
            status_phase22 = 1;
        }
    }

    return 0;
}


//パターンの決定1！！
int act_dif_phase25(int threthold)
{
    static int status_phase25 = 0;
    double distance = fcal_distance();
    double distL = get_L_distance();
    int dist_btw_F = get_sonorsensor();
    if(course == 1)
    {
        if(status_phase25 == 0)
        {
            encode_l_motor(40);
            encode_r_motor(10);
            if((distL > 14.0))
            {
                distance_reset();
                if(dist_btw_F < 10)
                {
                    pattern = 2;
                }
                else
                {
                    pattern = 1;
                }
                //printf("1:pattern%d\n",pattern);
                status_phase25 = 1;
            }
        }
        else if(status_phase25 == 1)
        {
            arm_control(0);
            timer = timer + 1;
            stop_wheel();
            if(timer > 100)
            {
                distance_reset();
                timer = 0;
                return END_PHASE;
            }
        }
    }
    else
    {
        if(status_phase25 == 0)
        {
            encode_r_motor(40);
            encode_l_motor(10);
            if((distL > 0.75))
            {
                distance_reset();
                if(dist_btw_F < 10)
                {
                    pattern = 2;
                }
                else
                {
                    pattern = 1;
                }
                //printf("1:pattern%d\n",pattern);
                status_phase25 = 1;
            }
        }
        else if(status_phase25 == 1)
        {
            arm_control(0);
            timer = timer + 1;
            stop_wheel();
            if(timer > 100)
            {
                distance_reset();
                timer = 0;
                return END_PHASE;
            }
        }
    }
    return 0;
}





//パターンの決定2！！
int act_dif_phase26(int threthold)
{
    double distance = fcal_distance();
    double distL = get_L_distance();
    int dist_btw_F = get_sonorsensor();
    static int status_phase26 = 0;
    arm_control(0);
    if(course == 1)
    {
        if(status_phase26 == 0)
        {
            spin(8);
            //printf("dist:%d\n",dist_btw_F);
            if((dist_btw_F < 30) && (distL > 4.70))
            {
                distance_reset();
                if(dist_btw_F < 27)
                {
                    pattern = 1;
                }
                else
                {
                    pattern = 2;
                }
                printf("2:pattern%d\n",pattern);
                status_phase26 = 1;
            }
        }
        else if(status_phase26 == 1)
        {
            arm_control(0);
            timer = timer + 1;
            stop_wheel();
            int distance = cal_distance();
            int light = get_reflectsensor();
            int dist_btw_C = get_sonorsensor();
            //printf("light = %d : dist = %d\n",light,dist_btw_C);
            //printf("%d\n",dist_btw_C);
            if(timer > 100)
            {
                if(dist_btw_F < 22)
                {
                    pattern = 1;
                }
                else
                {
                    pattern = 2;
                }
                printf("2:pattern%d\n",pattern);
                distance_reset();
                timer = 0;
                return END_PHASE;
            }
        }
    }
    else
    {
        if(status_phase26 == 0)
        {
            spin(-8);
            printf("dist:%d\n",dist_btw_F);
            if((dist_btw_F < 30) && (distL < -4.70))
            {
                distance_reset();
                if(dist_btw_F < 27)
                {
                    pattern = 1;
                }
                else
                {
                    pattern = 2;
                }
                printf("2:pattern%d\n",pattern);
                status_phase26 = 1;
            }
        }
        else if(status_phase26 == 1)
        {
            arm_control(0);
            timer = timer + 1;
            stop_wheel();
            int distance = cal_distance();
            int light = get_reflectsensor();
            int dist_btw_C = get_sonorsensor();
            //printf("light = %d : dist = %d\n",light,dist_btw_C);
            //printf("%d\n",dist_btw_C);
            if(timer > 100)
            {
                if(dist_btw_F < 22)
                {
                    pattern = 1;
                }
                else
                {
                    pattern = 2;
                }
                printf("2:pattern%d\n",pattern);
                distance_reset();
                timer = 0;
                return END_PHASE;
            }
        }
    }
    return 0;
}

int act_dif_phase27(int threthold)
{
    double distance = fcal_distance();
    double distL = get_L_distance();
    int dist_btw_F = get_sonorsensor();
    arm_control(0);
    if(course == 1)
    {
        if(pattern == 1)
        {
            if(status_phase24 == 0)
            {
                spin(-4);
                if(dist_btw_F > 40)
                {
                    status_phase24 = 1;
                    distance_reset();
                }
            }
            else if(status_phase24 == 1)
            {
                spin(3);
                if(distL > 4.40)
                {
                    status_phase24 = 2;
                    distance_reset();
                }
            }
            else if(status_phase24 == 2)
            {
                arm_control(0);
                timer = timer + 1;
                stop_wheel();
                int distance = cal_distance();
                int light = get_reflectsensor();
                int dist_btw_C = get_sonorsensor();
                //printf("light = %d : dist = %d\n",light,dist_btw_C);
                //printf("%d\n",dist_btw_C);
                if(timer > 10)
                {
                    distance_reset();
                    timer = 0;
                    return END_PHASE;
                }
            }
        }
        else if(pattern == 2)
        {
            spin(-5);
            if(distL < -3.45)
            {
                return END_PHASE;
                distance_reset();
            }
        }
    }
    else
    {
        if(pattern == 1)
        {
            if(status_phase24 == 0)
            {
                spin(4);
                if(dist_btw_F > 40)
                {
                    status_phase24 = 1;
                    distance_reset();
                }
            }
            else if(status_phase24 == 1)
            {
                spin(-3);
                if(distL < -4.40)
                {
                    status_phase24 = 2;
                    distance_reset();
                }
            }
            else if(status_phase24 == 2)
            {
                arm_control(0);
                timer = timer + 1;
                stop_wheel();
                int distance = cal_distance();
                int light = get_reflectsensor();
                int dist_btw_C = get_sonorsensor();
                //printf("light = %d : dist = %d\n",light,dist_btw_C);
                //printf("%d\n",dist_btw_C);
                if(timer > 10)
                {
                    distance_reset();
                    timer = 0;
                    return END_PHASE;
                }
            }
        }
        else if(pattern == 2)
        {
            spin(5);
            if(distL > 3.45)
            {
                return END_PHASE;
                distance_reset();
            }
        }
    }
    return 0;
}


int act_dif_phase28(int threthold)
{
    double distance = fcal_distance();
    double distL = get_L_distance();
    int light = get_reflectsensor();
    if(course == 1)
    {
        if(pattern == 1)
        {
            encode_l_motor(20);
            encode_r_motor(20);
            if(distance > 8.00)
            {
                distance_reset();
                return END_PHASE;
            }
        }
        else if(pattern == 2)
        {
            arm_control(15);
            if(distance < 9)
            {
                encode_l_motor(10);
                encode_r_motor(8);
            }
            else if(distance >= 9)
            {
                encode_l_motor(12);
                encode_r_motor(22);
            }
            if((distance > 10.0) && (light < 10))
            {
                distance_reset();
                return END_PHASE;
            }
        }
    }
    else
    {
        if(pattern == 1)
        {
            encode_l_motor(20);
            encode_r_motor(20);
            if(distance > 8.00)
            {
                distance_reset();
                return END_PHASE;
            }
        }
        else if(pattern == 2)
        {
            arm_control(15);
            if(distance < 9)
            {
                encode_r_motor(10);
                encode_l_motor(8);
            }
            else if(distance >= 9)
            {
                encode_r_motor(12);
                encode_l_motor(22);
            }
            if((distance > 10.0) && (light < 10))
            {
                distance_reset();
                return END_PHASE;
            }
        }
    }
    return 0;
}


int act_dif_phase29(int threthold)
{
    double distance = fcal_distance();
    double distL = get_L_distance();
    int light = get_reflectsensor();
    if(course == 1)
    {
        if(pattern == 1)
        {
            if(status_phase26 == 0)
            {
                //printf("%.2f\n",distL);
                encode_l_motor(0);
                encode_r_motor(8);
                if(distL > 1.80)
                {
                    distance_reset();
                    status_phase26 = 1;
                }
            }
            else if(status_phase26 == 1)
            {
                encode_l_motor(10);
                encode_r_motor(0);
                if(distance > 1.30)
                {
                    distance_reset();
                    status_phase26 = 2;
                }
            }
            else if(status_phase26 == 2)
            {
                encode_l_motor(-1);
                encode_r_motor(10);
                if(distance > 2.70)
                {
                    distance_reset();
                    status_phase26 = 3;
                }
            }
            else if(status_phase26 == 3)
            {
                encode_l_motor(10);
                encode_r_motor(0);
                if(distance >2.85)
                {
                    distance_reset();
                    status_phase26 = 4;
                }
            }
            else if(status_phase26 == 4)
            {
                encode_l_motor(-1);
                encode_r_motor(10);
                if(distance > 3.42)
                {
                    distance_reset();
                    status_phase26 = 5;
                }
            }
            else if(status_phase26 == 5)
            {
                encode_l_motor(14);
                encode_r_motor(-2);
                if((distance > 12.45) || ((distance > 10.5) &&  (light < 10)))
                {
                    distance_reset();
                    status_phase26 = 6;
                }
            }
            else if(status_phase26 == 6)
            {
                encode_l_motor(5);
                encode_r_motor(5);
                if((distance > 2))
                {
                    distance_reset();
                    return END_PHASE;
                }
            }
        }
        else if(pattern == 2)
        {
            return END_PHASE;
        }
    }
    else
    {
        if(pattern == 1)
        {
            if(status_phase26 == 0)
            {
                //printf("%.2f\n",distL);
                encode_r_motor(0);
                encode_l_motor(8);
                if(distL > 5.20)
                {
                    distance_reset();
                    status_phase26 = 1;
                }
            }
            else if(status_phase26 == 1)
            {
                encode_r_motor(10);
                encode_l_motor(0);
                if(distance > 1.30)
                {
                    distance_reset();
                    status_phase26 = 2;
                }
            }
            else if(status_phase26 == 2)
            {
                encode_r_motor(-1);
                encode_l_motor(10);
                if(distance > 2.70)
                {
                    distance_reset();
                    status_phase26 = 3;
                }
            }
            else if(status_phase26 == 3)
            {
                encode_r_motor(10);
                encode_l_motor(0);
                if(distance >2.85)
                {
                    distance_reset();
                    status_phase26 = 4;
                }
            }
            else if(status_phase26 == 4)
            {
                encode_r_motor(-1);
                encode_l_motor(10);
                if(distance > 3.42)
                {
                    distance_reset();
                    status_phase26 = 5;
                }
            }
            else if(status_phase26 == 5)
            {
                encode_r_motor(14);
                encode_l_motor(-2);
                if((distance > 11.45) || ((distance > 7.5) &&  (light < 10)))
                {
                    distance_reset();
                    status_phase26 = 6;
                }
            }
            else if(status_phase26 == 6)
            {
                encode_l_motor(5);
                encode_r_motor(5);
                if((distance > 0))
                {
                    distance_reset();
                    return END_PHASE;
                }
            }
        }
        else if(pattern == 2)
        {
            return END_PHASE;
        }
    }
    return 0;
}

//全フェイズ終了
int act_dif_phase30(int threthold)
{
    double distance = fcal_distance();
    double distL = get_L_distance();
    int light = get_reflectsensor();
    if(course == 1)
    {
        if(pattern == 1)
        {
            /*encode_l_motor(10);
            encode_r_motor(2);
            if(distance > 10)
            {
                distance_reset();
                return END_PHASE;
            }*/
            if(light < 5)
            {
                encode_l_motor(10);
                encode_r_motor(-5);
            }
            else
            {
                encode_l_motor(-5);
                encode_r_motor(10);
            }
            if(distance > 5.5)
            {
                distance_reset();
                return END_PHASE;
            }
        }
        //LT走行
        else if(pattern == 2)
        {
            arm_control(15);
            if(light > 8)
            {
                encode_l_motor(12);
                encode_r_motor(30);
            }
            else
            {
                encode_l_motor(30);
                encode_r_motor(-8);
            }
            if(distance > 20)
            {
                distance_reset();
                return END_PHASE;
            }
        }
    }
    else
    {
        if(pattern == 1)
        {
            /*encode_l_motor(10);
            encode_r_motor(2);
            if(distance > 10)
            {
                distance_reset();
                return END_PHASE;
            }*/
            if(light < 5)
            {
                encode_r_motor(10);
                encode_l_motor(-5);
            }
            else
            {
                encode_r_motor(-5);
                encode_l_motor(10);
            }
            if(distance > 5.5)
            {
                distance_reset();
                return END_PHASE;
            }
        }
        else if(pattern == 2)
        {
            arm_control(15);
            if(light > 5)
            {
                encode_r_motor(12);
                encode_l_motor(30);
            }
            else
            {
                encode_r_motor(30);
                encode_l_motor(-3);
            }
            if(distance > 20)
            {
                distance_reset();
                return END_PHASE;
            }
        }
    }
    return 0;
}

int act_dif_phase31(int threthold)
{
    int light = get_reflectsensor();
    double distance = fcal_distance();
    double distL = get_L_distance();
    int dist_btw_F = get_sonorsensor();
    if(pattern == 1)
    {
        return END_PHASE;
    }
    else if(pattern == 2)
    {
        return END_PHASE;
    }
    return 0;
}

int act_dif_phase32(int threthold)
{
    double distance = fcal_distance();
    double distL = get_L_distance();
    int light = get_reflectsensor();
    if(pattern == 1)
    {
        return END_PHASE;
    }
    if(pattern == 2)
    {
        return END_PHASE;
    }
    return 0;
}

//pattern1終了
int act_dif_phase33(int threthold)
{
    int light = get_reflectsensor();
    double distance = fcal_distance();
    double distL = get_L_distance();
    int dist_btw_F = get_sonorsensor();
    if(pattern == 1)
    {
        return END_PHASE;
    }
    else if(pattern == 2)
    {
        return END_PHASE;
    }
    return 0;
}


int act_dif_phase34(int threthold)
{
    double distance = fcal_distance();
    double distL = get_L_distance();
    if(pattern == 1)
    {
        return END_PHASE;
    }
    else if(pattern == 2)
    {
        return END_PHASE;
    }
    return 0;
}

//****************************************************************************************
// 関数名 : act_gir_phase1
// 引数 　: int   threthold - 閾値
// 
// 返り値 : END_PHASE or 0  - phase内容完了通知
// 概要 　: ガレージ攻略phase1の内容を行う。
//              →青色検知を行う。
// 作成者 :　辻
//****************************************************************************************
int act_gir_phase1(int threthold)
{
    int distance = cal_distance();
    int light = get_reflectsensor();
    //get_rgbsensor();
    arm_control(10);
    //run(15, 0);
    //encode_l_motor(14);
    //encode_r_motor(15);
    double turn = cal_turn(course,light+5,threthold,0.50,0.00);
    run(14,turn); 
    /*if(detect_blue() == 1)
    {
        stop_wheel();
        distance_reset();
        return END_PHASE;
    }*/
    if(distance > 20)
    {
        encode_l_motor(10);
        encode_r_motor(10);
        if(get_sonorsensor() < 10)
        {
            stop_wheel();
            timer++;
            if(timer > 3000)
            {
                //ETRoboc_notifyCompletedToSimulator();
            }
        }
    }
    return 0;
}

//****************************************************************************************
// 関数名 : act_gir_phase2
// 引数 　: int   threthold - 閾値
// 
// 返り値 : END_PHASE or 0  - phase内容完了通知
// 概要 　: ガレージ攻略phase2の内容を行う。
//                  →ブロック獲得に向けて、微調整を行う。
// 作成者 :　辻　
//****************************************************************************************
int act_gir_phase2(int threthold)
{
    double distance = fcal_distance();
    run(15, 0); 
    if(distance > 1.8)
    {
        stop_wheel();
        distance_reset();
        return END_PHASE;
    }
    return 0;
}

//****************************************************************************************
// 関数名 : act_gir_phase3
// 引数 　: int   threthold - 閾値
// 
// 返り値 : END_PHASE or 0  - phase内容完了通知
// 概要 　: ガレージ攻略phase3の内容を行う。
//                  →右に90°旋回する。
// 作成者 :　辻　
//****************************************************************************************
int act_gir_phase3(int threthold)
{
    if(pattern == 1)
    {
        encode_l_motor(30);
        encode_r_motor(30);
        if(sonar_alert() == 1)
        {
            return END_PHASE;
        }
    }
    else if(pattern == 2)
    {
        if(++timer > 50)
        {
            /*目安として122~128程度で90°回転(速度によって変化)*/
            if(do_angle_turning(128, 0,30) == 1)
            {
                timer = 0;
                return END_PHASE;
            }
        }
    }
    return 0;
}

//****************************************************************************************
// 関数名 : act_gir_phase4
// 引数 　: int   threthold - 閾値
// 
// 返り値 : END_PHASE or 0  - phase内容完了通知
// 概要 　: ガレージ攻略phase4の内容を行う。
//                  →黒線まで移動する。
// 作成者 :　辻　
//****************************************************************************************
int act_gir_phase4(int threthold)
{
    if(pattern == 1)
    {
        stop_wheel();
    }
    else if(pattern == 2)
    {
        if(++timer > 50)
        {
            int distance = cal_distance();
            arm_control(10);

            //steer_wheel(23, 0); //23以下が安定(ただし遅い)
            accel_run(20,100);
            if(distance > 80)
            {
            //stop_wheel();
            reset_accel_run();
            distance_reset();
            arm_control(8);
            timer = 0;
            return END_PHASE;
            }
        }
    }
    return 0;
}

//****************************************************************************************
// 関数名 : act_gir_phase5
// 引数 　: int   threthold - 閾値
// 
// 返り値 : END_PHASE or 0  - phase内容完了通知
// 概要 　: ガレージ攻略phase5の内容を行う。
//                  →ライントレースしながら、ブロックを抱える。
// 作成者 :　辻　
//****************************************************************************************
int act_gir_phase5(int threthold)
{
    int light = get_reflectsensor();
    int distance = cal_distance();
    //double turn = cal_turn(light,17,0.10,0.5);
    //printf("Light：%d\n",light);
    //run(45,turn);
    if(distance < 23)
    {
        if(light < 10)
        {
            encode_l_motor(20);
            encode_r_motor(5);
        }
        else
        {
            encode_l_motor(5);
            encode_r_motor(20);
        }
    }
    else if(distance >= 23)
    {
        encode_l_motor(20);
        encode_r_motor(20);
    }
    arm_control(8);
    //accel_run(12,40);
    if(distance > 24)
    {
        //stop_wheel();
        distance_reset();
        //reset_accel_run();
        return END_PHASE;
    }
    return 0;
}

//****************************************************************************************
// 関数名 : act_gir_phase6
// 引数 　: int   threthold - 閾値
// 
// 返り値 : END_PHASE or 0  - phase内容完了通知
// 概要 　: ガレージ攻略phase6の内容を行う。
//                  →左に180°旋回する。
// 作成者 :　辻　
//****************************************************************************************
int act_gir_phase6(int threthold)
{
    arm_control(12);
    if(++timer > 100)
    {
        if(do_dancing_turn(620,1,20) == 1)
        {
            timer = 0;
            return END_PHASE;
        }
    }
    return 0;
}

//****************************************************************************************
// 関数名 : act_gir_phase7
// 引数 　: int   threthold - 閾値
// 
// 返り値 : END_PHASE or 0  - phase内容完了通知
// 概要 　: ガレージ攻略phase7の内容を行う。
//                  →ブロックを抱えながら、線まで直進し、戻る。
// 作成者 :　辻
//****************************************************************************************
int act_gir_phase7(int threthold)
{
    arm_control(8);
    int distance = cal_distance();
    accel_run(15,90);
    if(distance > 92)
    {
        distance_reset();
        reset_accel_run();
        stop_wheel_slowly();    //ブロックのために緩やかに停止
        return END_PHASE;
    }
    return 0;
}

//****************************************************************************************
// 関数名 : act_gir_phase8
// 引数 　: int   threthold - 閾値
// 
// 返り値 : END_PHASE or 0  - phase内容完了通知
// 概要 　: ガレージ攻略phase8の内容を行う。
//                  →右に90°旋回する。
// 作成者 :　辻　
//****************************************************************************************
int act_gir_phase8(int threthold)
{
    arm_control(12);
    if(++timer > 50)
    {
        if(do_dancing_turn(260,0,45) == 1)
        {
            timer = 0;
            return END_PHASE;
        }
    }
    return 0;
}

//****************************************************************************************
// 関数名 : act_gir_phase9
// 引数 　: int   threthold - 閾値
// 
// 返り値 : END_PHASE or 0  - phase内容完了通知
// 概要 　: ガレージ攻略phase9の内容を行う。
//                  →直進し、ガレージを検知して停止する。
// 作成者 :　辻　
//****************************************************************************************
int act_gir_phase9(int threthold)
{
    if(++timer > 50)
    {
        arm_control(10);
        accel_run(30,70);
        if(sonar_alert() == 1)
        {
            printf("END");
            stop_wheel();
            reset_accel_run();
            stop_arm_motor();
            timer = 0;
            return END_PHASE;
        }
    }
    return 0;
}

int act_gir_phase10(int threthold)
{
    if(++timer > 1000)
    {
        timer = 0;
        return END_PHASE;
    }
    return 0;
}