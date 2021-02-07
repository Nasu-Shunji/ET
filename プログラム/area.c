#include "area.h"
/*******************************************
*                                          *
*   spd_phase_number = 0   -> phase1       *
*   spd_phase_number = 1   -> phase2       *
*   spd_phase_number = 2   -> phase3       *
*   spd_phase_number = 3   -> phase4       *
*                                          *
*******************************************/
static int spd_phase_number = 0;//スピード競技フェイズ指定子(上記に従って変更する)
static int dif_phase_number = 0;//難所フェイズ指定子
static int gir_phase_number = 0;


static int end_spd_phase1 = 0;//スピードフェイズ1終了指定子
static int end_spd_phase2 = 0;//スピードフェイズ2終了指定子
static int end_spd_phase3 = 0;//スピードフェイズ3終了指定子
static int end_spd_phase4 = 0;//スピードフェイズ4終了指定子
static int end_spd_phase5 = 0;//スピードフェイズ5終了指定子
static int end_spd_phase6 = 0;//スピードフェイズ6終了指定子
static int end_spd_phase7 = 0;//スピードフェイズ7終了指定子
static int end_spd_phase8 = 0;//スピードフェイズ8終了指定子
static int end_spd_phase9 = 0;//スピードフェイズ9終了指定子
static int end_spd_phase10 = 0;//スピードフェイズ10終了指定子
static int end_spd_phase11 = 0;//スピードフェイズ11終了指定子
static int end_spd_phase12 = 0;//スピードフェイズ12終了指定子
static int end_spd_phase13 = 0;//スピードフェイズ13終了指定子
static int end_spd_phase14 = 0;//スピードフェイズ13終了指定子
static int end_spd_phase15 = 0;//スピードフェイズ13終了指定子
static int end_spd_phase16 = 0;//スピードフェイズ13終了指定子
static int end_spd_phase17 = 0;//スピードフェイズ13終了指定子


static int end_dif_phase1 = 0;//難所1終了指定子
static int end_dif_phase2 = 0;//難所2終了指定子
static int end_dif_phase3 = 0;//難所3終了指定子
static int end_dif_phase4 = 0;//難所4終了指定子
static int end_dif_phase5 = 0;//難所5終了指定子
static int end_dif_phase6 = 0;//難所6終了指定子
static int end_dif_phase7 = 0;//難所7終了指定子
static int end_dif_phase8 = 0;//難所8終了指定子
static int end_dif_phase9 = 0;//難所9終了指定子
static int end_dif_phase10 = 0;//難所10終了指定子
static int end_dif_phase11 = 0;//難所11終了指定子
static int end_dif_phase12 = 0;//難所12終了指定子
static int end_dif_phase13 = 0;//難所13終了指定子
static int end_dif_phase14 = 0;//難所14終了指定子
static int end_dif_phase15 = 0;//難所15終了指定子
static int end_dif_phase16 = 0;//難所16終了指定子
static int end_dif_phase17 = 0;//難所17終了指定子
static int end_dif_phase18 = 0;//難所18終了指定子
static int end_dif_phase19 = 0;//難所19終了指定子
static int end_dif_phase20 = 0;//難所20終了指定子
static int end_dif_phase21 = 0;//難所11終了指定子
static int end_dif_phase22 = 0;//難所12終了指定子
static int end_dif_phase23 = 0;//難所13終了指定子
static int end_dif_phase24 = 0;//難所14終了指定子
static int end_dif_phase25 = 0;//難所15終了指定子
static int end_dif_phase26 = 0;//難所16終了指定子
static int end_dif_phase27 = 0;//難所17終了指定子
static int end_dif_phase28 = 0;//難所18終了指定子
static int end_dif_phase29 = 0;//難所19終了指定子
static int end_dif_phase30 = 0;//難所20終了指定子
static int end_dif_phase31 = 0;//難所19終了指定子
static int end_dif_phase32 = 0;//難所20終了指定子
static int end_dif_phase33 = 0;//難所33終了指定子

static int end_gir_phase1 = 0;  //ガレージphase1終了指定子
static int end_gir_phase2 = 0;  //ガレージphase2終了指定子
static int end_gir_phase3 = 0;  //ガレージphase3終了指定子
static int end_gir_phase4 = 0;  //ガレージphase4終了指定子
static int end_gir_phase5 = 0;  //ガレージphase5終了指定子
static int end_gir_phase6 = 0;  //ガレージphase6終了指定子
static int end_gir_phase7 = 0;  //ガレージphase7終了指定子
static int end_gir_phase8 = 0;  //ガレージphase8終了指定子
static int end_gir_phase9 = 0;  //ガレージphase9終了指定子
static int end_gir_phase10 = 0;  //ガレージphase10終了指定子
static int end_gir_phase11 = 0;  //ガレージphase11終了指定子
static int end_gir_phase12 = 0;  //ガレージphase12終了指定子
static int end_gir_phase13 = 0;  //ガレージphase13終了指定子
static int end_gir_phase14 = 0;  //ガレージphase13終了指定子
static int end_gir_phase15 = 0;  //ガレージphase13終了指定子
static int end_gir_phase16 = 0;  //ガレージphase13終了指定子
static int end_gir_phase17 = 0;  //ガレージphase13終了指定子
    
static int threthold = 0;//閾値

//*****************************************************************************
// 関数名 : select_area
// 引数 　: int   select_area_key - 現在のエリア
// 
// 返り値 : int   area_key        - 次のエリア
// 概要 　: 次行うべきエリアの決定を行う。各エリアが終了次第呼び出す。
//          呼び出すたびにエリアが一つずつ遷移する
// 追加   : (例外処理:引数が配列サイズよりも大きいときの処理)
//*****************************************************************************
int select_area(int select_area_key)
{
    enum AREA_NUM AN[] = {  cal_area,
                            spd_area,
                            dif_area,
                            gir_area,
                            END_AREA
                         };
    int area_key = AN[select_area_key];
    return area_key;
}

//*****************************************************************************
// 関数名 : act_cal_area
// 引数 　: 無し
// 
// 返り値 : END        - 終了通知
// 概要 　: キャリブレーションエリアの内容を行う
//          今回、キャリブレーションの時間がないため余り意味はない
//*****************************************************************************
int act_cal_area()
{
    int white = 40;
    int black = 13;
    threthold = (white + black) / 2;
    return END_AREA; 
}

//*****************************************************************************
// 関数名 : act_spd_area
// 引数 　: 無し
// 
// 返り値 : END_AREA or 0       - エリア内容完了通知
// 概要 　: スピード競技エリアの内容を行う
//          主に那須君の担当場所(ある程度、初めは作ったから参考にしてみて)
//*****************************************************************************
int act_spd_area(int course_key)
{
    switch (spd_phase_number)
    {
        case 0://phase0 -> 最初の設定
            set_course(course_key);
            spd_phase_number = select_spd_phase(spd_phase_number);
            break;
        case 1://phase1 -> 最初のストレート
            end_spd_phase1 = act_spd_phase1(threthold);
            if(end_spd_phase1 == 1)
            {
                spd_phase_number = select_spd_phase(spd_phase_number);
            }
            break;
        case 2://phase2 -> 次のカーブ
            end_spd_phase2 = act_spd_phase2(threthold);
            if(end_spd_phase2 == 1)
            {
                spd_phase_number = select_spd_phase(spd_phase_number);
            }
            break;
        case 3://phase3 -> 次のストレート
            end_spd_phase3 = act_spd_phase3(threthold);
            if(end_spd_phase3 == 1)
            {
                spd_phase_number = select_spd_phase(spd_phase_number);
            }
            break;
        case 4://phase4 -> 次のカーブ
            end_spd_phase4 = act_spd_phase4(threthold);
            if(end_spd_phase4 == 1)
            {
                spd_phase_number = select_spd_phase(spd_phase_number);
            }
            break;
        case 5://phase5 -> 次のストレート
            end_spd_phase5 = act_spd_phase5(threthold);
            if(end_spd_phase5 == 1)
            {
                spd_phase_number = select_spd_phase(spd_phase_number);
            }
            break;
        case 6://phase6 -> 次のカーブ
            end_spd_phase6 = act_spd_phase6(threthold);
            if(end_spd_phase6 == 1)
            {
                spd_phase_number = select_spd_phase(spd_phase_number);
            }
            break;
        case 7://phase6 -> 次のカーブ
            end_spd_phase7 = act_spd_phase7(threthold);
            if(end_spd_phase7 == 1)
            {
                spd_phase_number = select_spd_phase(spd_phase_number);
            }
            break;
        case 8://phase6 -> 次のカーブ
            end_spd_phase8 = act_spd_phase8(threthold);
            if(end_spd_phase8 == 1)
            {
                spd_phase_number = select_spd_phase(spd_phase_number);
            }
            break;
        case 9://phase6 -> 次のカーブ
            end_spd_phase9 = act_spd_phase9(threthold);
            if(end_spd_phase9 == 1)
            {
                spd_phase_number = select_spd_phase(spd_phase_number);
            }
            break;
        case 10://phase6 -> 次のカーブ
            end_spd_phase10 = act_spd_phase10(threthold);
            if(end_spd_phase10 == 1)
            {
                spd_phase_number = select_spd_phase(spd_phase_number);
            }
            break;
        case 11://phase6 -> 次のカーブ
            end_spd_phase11 = act_spd_phase11(threthold);
            if(end_spd_phase11 == 1)
            {
                spd_phase_number = select_spd_phase(spd_phase_number);
            }
            break;
        case 12://phase6 -> 次のカーブ
            end_spd_phase12 = act_spd_phase12(threthold);
            if(end_spd_phase12 == 1)
            {
                spd_phase_number = select_spd_phase(spd_phase_number);
            }
            break;
        case 13://phase6 -> 次のカーブ
            end_spd_phase13 = act_spd_phase13(threthold);
            if(end_spd_phase13 == 1)
            {
                spd_phase_number = select_spd_phase(spd_phase_number);
            }
            break;
        case 14://phase6 -> 次のカーブ
            end_spd_phase14 = act_spd_phase14(threthold);
            if(end_spd_phase14 == 1)
            {
                spd_phase_number = select_spd_phase(spd_phase_number);
            }
            break;
        case 15://phase6 -> 次のカーブ
            end_spd_phase15 = act_spd_phase15(threthold);
            if(end_spd_phase15 == 1)
            {
                spd_phase_number = select_spd_phase(spd_phase_number);
            }
            break;
        case 16://phase6 -> 次のカーブ
            end_spd_phase16 = act_spd_phase16(threthold);
            if(end_spd_phase16 == 1)
            {
                spd_phase_number = select_spd_phase(spd_phase_number);
            }
            break;
        case 17://phase6 -> 次のカーブ
            end_spd_phase17 = act_spd_phase17(threthold);
            if(end_spd_phase17 == 1)
            {
                spd_phase_number = select_spd_phase(spd_phase_number);
            }
            break;
    }
    //全phase終了判定(phaseが増えるたびにここも増えていく)　-> ちょっとめんどくさいから効率がいい方法を探そう...
    if((end_spd_phase1 == 1) && 
       (end_spd_phase2 == 1) && 
       (end_spd_phase3 == 1) && 
       (end_spd_phase4 == 1) && 
       (end_spd_phase5 == 1) && 
       (end_spd_phase6 == 1) && 
       (end_spd_phase7 == 1) && 
       (end_spd_phase8 == 1) && 
       (end_spd_phase9 == 1) && 
       (end_spd_phase10 == 1) && 
       (end_spd_phase11 == 1) && 
       (end_spd_phase12 == 1) && 
       (end_spd_phase13 == 1) &&
       (end_spd_phase14 == 1) &&
       (end_spd_phase15 == 1) &&
       (end_spd_phase16 == 1) &&
       (end_spd_phase17 == 1))
    {
        return END_AREA;
    }
    return 0;
}

//*****************************************************************************
// 関数名 : act_dif_area
// 引数 　: 無し
// 
// 返り値 : END or 0       - 終了通知
// 概要 　: 難所エリアの内容を行う
//          主に大橋の担当場所(概要は作った、中身はまだない)
//          大体はスピード競技エリアと同じになる予定
//*****************************************************************************
int act_dif_area()
{
   switch (dif_phase_number)
    {
        case 0://phase0
            dif_phase_number = select_dif_phase(dif_phase_number);
            break;
        case 1://phase1
            end_dif_phase1 = act_dif_phase1(threthold);
            if(end_dif_phase1 == 1)
            {
                dif_phase_number = select_dif_phase(dif_phase_number);
            }
            break;
        case 2://phase2
            end_dif_phase2 = act_dif_phase2(threthold);
            if(end_dif_phase2 == 1)
            {
                dif_phase_number = select_dif_phase(dif_phase_number);
            }
            break;
        case 3://phase3
            end_dif_phase3 = act_dif_phase3(threthold);
            if(end_dif_phase3 == 1)
            {
                dif_phase_number = select_dif_phase(dif_phase_number);
            }
            break;
        case 4://phase4
            end_dif_phase4 = act_dif_phase4(threthold);
            if(end_dif_phase4 == 1)
            {
                dif_phase_number = select_dif_phase(dif_phase_number);
            }
            break;
        case 5://phase5
            end_dif_phase5 = act_dif_phase5(threthold);
            if(end_dif_phase5 == 1)
            {
                dif_phase_number = select_dif_phase(dif_phase_number);
            }
            break;
        case 6://phase6
            end_dif_phase6 = act_dif_phase6(threthold);
            if(end_dif_phase6 == 1)
            {
                dif_phase_number = select_dif_phase(dif_phase_number);
            }
            break;
        case 7://phase7
            end_dif_phase7 = act_dif_phase7(threthold);
            if(end_dif_phase7 == 1)
            {
                dif_phase_number = select_dif_phase(dif_phase_number);
            }
            break;
        case 8://phase8
            end_dif_phase8 = act_dif_phase8(threthold);
            if(end_dif_phase8 == 1)
            {
                dif_phase_number = select_dif_phase(dif_phase_number);
            }
            break;
        case 9://phase9
            end_dif_phase9 = act_dif_phase9(threthold);
            if(end_dif_phase9 == 1)
            {
                dif_phase_number = select_dif_phase(dif_phase_number);
            }
            break;
        case 10://phase10
            end_dif_phase10 = act_dif_phase10(threthold);
            if(end_dif_phase10 == 1)
            {
                dif_phase_number = select_dif_phase(dif_phase_number);
            }
            break;
        case 11://phase11
            end_dif_phase11 = act_dif_phase11(threthold);
            if(end_dif_phase11 == 1)
            {
                dif_phase_number = select_dif_phase(dif_phase_number);
            }
            break;
        case 12://phase12
            end_dif_phase12 = act_dif_phase12(threthold);
            if(end_dif_phase12 == 1)
            {
                dif_phase_number = select_dif_phase(dif_phase_number);
            }
            break;
        case 13://phase13
            end_dif_phase13 = act_dif_phase13(threthold);
            if(end_dif_phase13 == 1)
            {
                dif_phase_number = select_dif_phase(dif_phase_number);
            }
            break;
        case 14://phase14
            end_dif_phase14 = act_dif_phase14(threthold);
            if(end_dif_phase14 == 1)
            {
                dif_phase_number = select_dif_phase(dif_phase_number);
            }
            break;
        case 15://phase15
            end_dif_phase15 = act_dif_phase15(threthold);
            if(end_dif_phase15 == 1)
            {
                dif_phase_number = select_dif_phase(dif_phase_number);
            }
            break;
        case 16://phase16
            end_dif_phase16 = act_dif_phase16(threthold);
            if(end_dif_phase16 == 1)
            {
                dif_phase_number = select_dif_phase(dif_phase_number);
            }
            break;
        case 17://phase17
            end_dif_phase17 = act_dif_phase17(threthold);
            if(end_dif_phase17 == 1)
            {
                dif_phase_number = select_dif_phase(dif_phase_number);
            }
            break;
        case 18://phase18
            end_dif_phase18 = act_dif_phase18(threthold);
            if(end_dif_phase18 == 1)
            {
                dif_phase_number = select_dif_phase(dif_phase_number);
            }
            break;
        case 19://phase19
            end_dif_phase19 = act_dif_phase19(threthold);
            if(end_dif_phase19 == 1)
            {
                dif_phase_number = select_dif_phase(dif_phase_number);
            }
            break;
        case 20://phase20
            end_dif_phase20 = act_dif_phase20(threthold);
            if(end_dif_phase20 == 1)
            {
                dif_phase_number = select_dif_phase(dif_phase_number);
            }
            break;
        case 21://phase21
            end_dif_phase21 = act_dif_phase21(threthold);
            if(end_dif_phase21 == 1)
            {
                dif_phase_number = select_dif_phase(dif_phase_number);
            }
            break;
        case 22://phase22
            end_dif_phase22 = act_dif_phase22(threthold);
            if(end_dif_phase22 == 1)
            {
                dif_phase_number = select_dif_phase(dif_phase_number);
            }
            break;
        case 23:
            end_dif_phase23 = act_dif_phase23(threthold);
            if(end_dif_phase23 == 1)
            {
                dif_phase_number = select_dif_phase(dif_phase_number);
            }
            break;
        case 24:
            end_dif_phase24 = act_dif_phase24(threthold);
            if(end_dif_phase24 == 1)
            {
                dif_phase_number = select_dif_phase(dif_phase_number);
            }
            break;
        case 25:
            end_dif_phase25 = act_dif_phase25(threthold);
            if(end_dif_phase25 == 1)
            {
                dif_phase_number = select_dif_phase(dif_phase_number);
            }
            break;
        case 26:
            end_dif_phase26 = act_dif_phase26(threthold);
            if(end_dif_phase26 == 1)
            {
                dif_phase_number = select_dif_phase(dif_phase_number);
            }
            break;
        case 27:
            end_dif_phase27 = act_dif_phase27(threthold);
            if(end_dif_phase27 == 1)
            {
                dif_phase_number = select_dif_phase(dif_phase_number);
            }
            break;
        case 28:
            end_dif_phase28 = act_dif_phase28(threthold);
            if(end_dif_phase28 == 1)
            {
                dif_phase_number = select_dif_phase(dif_phase_number);
            }
            break;
        case 29:
            end_dif_phase29 = act_dif_phase29(threthold);
            if(end_dif_phase29 == 1)
            {
                dif_phase_number = select_dif_phase(dif_phase_number);
            }
            break;
        case 30:
            end_dif_phase30 = act_dif_phase30(threthold);
            if(end_dif_phase30 == 1)
            {
                dif_phase_number = select_dif_phase(dif_phase_number);
            }
            break;
        case 31:
            end_dif_phase31 = act_dif_phase31(threthold);
            if(end_dif_phase31 == 1)
            {
                dif_phase_number = select_dif_phase(dif_phase_number);
            }
            break;
        case 32:
            end_dif_phase32 = act_dif_phase32(threthold);
            if(end_dif_phase32 == 1)
            {
                dif_phase_number = select_dif_phase(dif_phase_number);
            }
            break;
        case 33:
            end_dif_phase33 = act_dif_phase33(threthold);
            if(end_dif_phase33 == 1)
            {
                dif_phase_number = select_dif_phase(dif_phase_number);
            }
            break;
    }
    //全phase終了判定(phaseが増えるたびにここも増えていく)　-> ちょっとめんどくさいから効率がいい方法を探そう...
    if((end_dif_phase1 == 1) && 
       (end_dif_phase2 == 1) && 
       (end_dif_phase3 == 1) && 
       (end_dif_phase4 == 1) && 
       (end_dif_phase5 == 1) && 
       (end_dif_phase6 == 1) &&
       (end_dif_phase7 == 1) && 
       (end_dif_phase8 == 1) && 
       (end_dif_phase9 == 1) && 
       (end_dif_phase10 == 1) && 
       (end_dif_phase11 == 1) && 
       (end_dif_phase12 == 1) &&
       (end_dif_phase13 == 1) && 
       (end_dif_phase14 == 1) && 
       (end_dif_phase15 == 1) && 
       (end_dif_phase16 == 1) && 
       (end_dif_phase17 == 1) && 
       (end_dif_phase18 == 1) &&
       (end_dif_phase19 == 1) &&
       (end_dif_phase20 == 1) &&
       (end_dif_phase21 == 1) &&
       (end_dif_phase22 == 1) &&
       (end_dif_phase23 == 1) &&
       (end_dif_phase24 == 1) &&
       (end_dif_phase25 == 1) &&
       (end_dif_phase26 == 1) &&
       (end_dif_phase27 == 1) &&
       (end_dif_phase28 == 1) &&
       (end_dif_phase29 == 1) &&
       (end_dif_phase30 == 1) &&
       (end_dif_phase31 == 1) &&
       (end_dif_phase32 == 1) &&
       (end_dif_phase33 == 1))
    {
        printf("fin_dif\n");
        return END_AREA;
    }
    return 0; 
}

//*****************************************************************************
// 関数名 : act_gir_area
// 引数 　: 無し
// 
// 返り値 : END or 0       - 終了通知
// 概要 　: 難所エリアの内容を行う
//          主に辻君、山本君の担当場所(概要は作った、中身はまだない)
//          大体はスピード競技エリアと同じになる予定
//*****************************************************************************
int act_gir_area()
{
    switch(gir_phase_number)
    {
        case 0: //phase_0 初期設定
            //printf("gir_area!!\n");
            gir_phase_number = select_gir_phase(gir_phase_number);
            break;
        case 1:
            end_gir_phase1 = act_gir_phase1(threthold);
            if(end_gir_phase1 == 1)
            {
                gir_phase_number = select_gir_phase(gir_phase_number);
            }
            break;
        case 2:
            end_gir_phase2 = act_gir_phase2(threthold);
            if(end_gir_phase2 == 1)
            {
                gir_phase_number = select_gir_phase(gir_phase_number);
            }
            break;
        case 3:
            end_gir_phase3 = act_gir_phase3(threthold);
            if(end_gir_phase3 == 1)
            {
                gir_phase_number = select_gir_phase(gir_phase_number);
            }
            break;
        case 4:
            end_gir_phase4 = act_gir_phase4(threthold);
            if(end_gir_phase4 == 1)
            {
                gir_phase_number = select_gir_phase(gir_phase_number);
            }
            break;
        case 5:
            end_gir_phase5 = act_gir_phase5(threthold);
            if(end_gir_phase5 == 1)
            {
                gir_phase_number = select_gir_phase(gir_phase_number);
            }
            break;
        case 6:
            end_gir_phase6 = act_gir_phase6(threthold);
            if(end_gir_phase6 == 1)
            {
                gir_phase_number = select_gir_phase(gir_phase_number);
            }
            break;
        case 7:
            end_gir_phase7 = act_gir_phase7(threthold);
            if(end_gir_phase7 == 1)
            {
                gir_phase_number = select_gir_phase(gir_phase_number);
            }
            break;
        case 8:
            end_gir_phase8 = act_gir_phase8(threthold);
            if(end_gir_phase8 == 1)
            {
                gir_phase_number = select_gir_phase(gir_phase_number);
            }
            break;
        case 9:
            end_gir_phase9 = act_gir_phase9(threthold);
            if(end_gir_phase9 == 1)
            {
                gir_phase_number = select_gir_phase(gir_phase_number);
            }
            break;
        case 10:
            end_gir_phase10 = act_gir_phase10(threthold);
            if(end_gir_phase10 == 1)
            {
                gir_phase_number = select_gir_phase(gir_phase_number);
            }
            break;
    }
    if((end_gir_phase1 == 1) && 
       (end_gir_phase2 == 1) && 
       (end_gir_phase3 == 1) && 
       (end_gir_phase4 == 1) &&
       (end_gir_phase5 == 1) &&
       (end_gir_phase6 == 1) &&
       (end_gir_phase7 == 1) &&
       (end_gir_phase8 == 1) &&
       (end_gir_phase9 == 1) &&
       (end_gir_phase10 == 1))
    {
        return END_AREA;
    }
    return 0;
}