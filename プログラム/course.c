#include "course.h"
#include "stdio.h"
static int course_key = 0;//コース指定子
/************************************
*                                   *
*   area_key = 0,1 -> cal_area      *
*   area_key = 2   -> spd_area      *
*   area_key = 3   -> dif_area      *
*   area_key = 4   -> gir_area      *
*                                   *
************************************/
static int area_key = 0;//エリア指定子(上記に従って担当する箇所の数字に変えること!)

static int end_cal_area = 0;//キャリブレーションエリア終了指定子
static int end_spd_area = 0;//スピード競技エリア終了指定子
static int end_dif_area = 0;//難所エリア終了指定子
static int end_gir_area = 0;//ガレージエリア終了指定子

//*****************************************************************************
// 関数名 : select_course
// 引数 　: int   select_course_key - コース指定子
// 
// 返り値 : int   course_key        - コース指定子
// 概要 　: コースの決定を行う。実機ではボタンを押して決定を行いたかった！！
//*****************************************************************************
int select_course(int select_course_key)
{
    if(select_course_key == 1)
    {
        course_key = L_COURSE;
    }
    else
    {
        course_key = R_COURSE;
    }
    return 1;
}

//**************************************************************************************
// 関数名 : act_course
// 引数 　: 無し
// 
// 返り値 : END_COURSE or 0        - コース内容完了通知
// 概要 　: コースクラスが各エリアクラスの「実行する」を行う。
//          各エリアが終了次第フラグを立て、最終的にすべてのフラグが1なら完了通知[1]を返す
//**************************************************************************************
int act_course()
{
    switch(area_key)
    {
        case 0:
        {
            printf("ok!!\n");
            area_key = select_area(area_key);//各エリア指定子(上記に従って変更を行う)
            break;
        }
        case 1:
        {
            end_cal_area = act_cal_area();
            if(end_cal_area == 1)
            {
                area_key = select_area(area_key);
            }
            break;
        }
        case 2:
        {
            end_spd_area = act_spd_area(course_key);
            if(end_spd_area == 1)
            {
                area_key = select_area(area_key);
            }
            break;
        }
        case 3:
        {
            end_dif_area = act_dif_area();
            if(end_dif_area == 1)
            {
                area_key = select_area(area_key);
            }
            break;
        }
        case 4:
        {
            end_gir_area = act_gir_area();
            if(end_gir_area == 1)
            {
                area_key = select_area(area_key);
            }
            break;
        }
    }
    if((end_cal_area == 1) && (end_spd_area == 1) && (end_dif_area == 1) && (end_gir_area == 1))
    {
        return END_COURSE;
    }
    return 0;
}