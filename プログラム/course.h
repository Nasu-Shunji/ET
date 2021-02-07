#include "area.h"

#define END_COURSE 1
#pragma once
enum COURSE_NUM
{
    L_COURSE = 1,
    R_COURSE = -1
};

int select_course(int select_course_key);