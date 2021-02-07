#include "phase.h"
#define END_AREA 1
#pragma once
enum AREA_NUM
{
    cal_area = 1,
    spd_area = 2,
    dif_area = 3,
    gir_area = 4
};

int select_area(int select_area_key);
int act_cal_area();
int act_spd_area(int course_key);
int act_dif_area();
int act_gir_area();
