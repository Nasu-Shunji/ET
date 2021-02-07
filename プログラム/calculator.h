#include "device.h"

double cal_turn(int course,int light,int threthold,double KP,double KI);
int arm_control(int goal_angle);
int cal_distance();
double get_L_distance();
double fcal_distance();
int do_angle_tuning(int threshold, int direction, unsigned int swing_speed);
int do_dancing_turn(int threshold, int direction, int swing_speed);