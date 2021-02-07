#include "device.h"
#include "calculator.h"
#include "run.h"
#include "etroboc_ext.h"
#define END_PHASE 1
void set_course(int course_key);
#pragma once
//以下、競技エリアフェイズ
enum SPD_PHASE_NUM  {
                        PHASE1 = 1,
                        PHASE2 = 2,
                        PHASE3 = 3,
                        PHASE4 = 4,
                        PHASE5 = 5,
                        PHASE6 = 6,
                        PHASE7 = 7,
                        PHASE8 = 8,
                        PHASE9 = 9,
                        PHASE10 = 10,
                        PHASE11 = 11,
                        PHASE12 = 12,
                        PHASE13 = 13,
                        PHASE14 = 14,
                        PHASE15 = 15,
                        PHASE16 = 16,
                        PHASE17 = 17
};

//以下、難所エリアフェイズ
enum DIF_PHASE_NUM  {
                        D_PHASE1 = 1,
                        D_PHASE2 = 2,
                        D_PHASE3 = 3,
                        D_PHASE4 = 4,
                        D_PHASE5 = 5,
                        D_PHASE6 = 6,
                        D_PHASE7 = 7,
                        D_PHASE8 = 8,
                        D_PHASE9 = 9,
                        D_PHASE10 = 10,
                        D_PHASE11 = 11,
                        D_PHASE12 = 12,
                        D_PHASE13 = 13,
                        D_PHASE14 = 14,
                        D_PHASE15 = 15,
                        D_PHASE16 = 16,
                        D_PHASE17 = 17,
                        D_PHASE18 = 18,
                        D_PHASE19 = 19,
                        D_PHASE20 = 20,
                        D_PHASE21 = 21,
                        D_PHASE22 = 22,
                        D_PHASE23 = 23,
                        D_PHASE24 = 24,
                        D_PHASE25 = 25,
                        D_PHASE26 = 26,
                        D_PHASE27 = 27,
                        D_PHASE28 = 28,
                        D_PHASE29 = 29,
                        D_PHASE30 = 30,
                        D_PHASE31 = 31,
                        D_PHASE32 = 32,
                        D_PHASE33 = 33,
                        D_PHASE34 = 34,
                        D_PHASE35 = 35,
                        D_PHASE36 = 36,
                        D_PHASE37 = 37,
                        D_PHASE38 = 38,
                        D_PHASE39 = 39,
                        D_PHASE40 = 40
};

//以下、ガレージエリアフェイズ
enum GIR_PHASE_NUM  {
    G_PHASE1 = 1,
    G_PHASE2 = 2,
    G_PHASE3 = 3,
    G_PHASE4 = 4,
    G_PHASE5 = 5,
    G_PHASE6 = 6,
    G_PHASE7 = 7,
    G_PHASE8 = 8,
    G_PHASE9 = 9,
    G_PHASE10 = 10,
    G_PHASE11 = 11,
    G_PHASE12 = 12,
    G_PHASE13 = 13,
    G_PHASE14 = 14,
    G_PHASE15 = 15,
    G_PHASE16 = 16,
    G_PHASE17 = 17
};
//以下、競技エリアフェイズ関数
int select_spd_phase(int select_spd_phase_key);
int act_spd_phase1(int threthold);
int act_spd_phase2(int threthold);
int act_spd_phase3(int threthold);
int act_spd_phase4(int threthold);
int act_spd_phase5(int threthold);
int act_spd_phase6(int threthold);
int act_spd_phase7(int threthold);
int act_spd_phase8(int threthold);
int act_spd_phase9(int threthold);
int act_spd_phase10(int threthold);
int act_spd_phase11(int threthold);
int act_spd_phase12(int threthold);
int act_spd_phase13(int threthold);
int act_spd_phase14(int threthold);
int act_spd_phase15(int threthold);
int act_spd_phase16(int threthold);
int act_spd_phase17(int threthold);


int select_dif_phase(int select_spd_phase_key);
int act_dif_phase1(int threthold);
int act_dif_phase2(int threthold);
int act_dif_phase3(int threthold);
int act_dif_phase4(int threthold);
int act_dif_phase5(int threthold);
int act_dif_phase6(int threthold);
int act_dif_phase7(int threthold);
int act_dif_phase8(int threthold);
int act_dif_phase9(int threthold);
int act_dif_phase10(int threthold);
int act_dif_phase11(int threthold);
int act_dif_phase12(int threthold);
int act_dif_phase13(int threthold);
int act_dif_phase14(int threthold);
int act_dif_phase15(int threthold);
int act_dif_phase16(int threthold);
int act_dif_phase17(int threthold);
int act_dif_phase18(int threthold);
int act_dif_phase19(int threthold);
int act_dif_phase20(int threthold);
int act_dif_phase21(int threthold);
int act_dif_phase22(int threthold);
int act_dif_phase23(int threthold);
int act_dif_phase24(int threthold);
int act_dif_phase25(int threthold);
int act_dif_phase26(int threthold);
int act_dif_phase27(int threthold);
int act_dif_phase28(int threthold);
int act_dif_phase29(int threthold);
int act_dif_phase30(int threthold);
int act_dif_phase31(int threthold);
int act_dif_phase32(int threthold);
int act_dif_phase33(int threthold);
int act_dif_phase34(int threthold);
int act_dif_phase35(int threthold);
int act_dif_phase36(int threthold);
int act_dif_phase37(int threthold);
int act_dif_phase38(int threthold);
int act_dif_phase39(int threthold);
int act_dif_phase40(int threthold);

//以下、ガレージエリアフェイズ関数
int select_gir_phase(int select_gir_phase_key);
int act_gir_phase1(int threthold);
int act_gir_phase2(int threthold);
int act_gir_phase3(int threthold);
int act_gir_phase4(int threthold);
int act_gir_phase5(int threthold);
int act_gir_phase6(int threthold);
int act_gir_phase7(int threthold);
int act_gir_phase8(int threthold);
int act_gir_phase9(int threthold);
int act_gir_phase10(int threthold);
int act_gir_phase11(int threthold);
int act_gir_phase12(int threthold);
int act_gir_phase13(int threthold);
int act_gir_phase14(int threthold);
int act_gir_phase15(int threthold);
int act_gir_phase16(int threthold);
int act_gir_phase17(int threthold);