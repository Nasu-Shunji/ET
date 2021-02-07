#include "ev3api.h"
#pragma once
/****************************************
 *  センサー、モーターの接続を定義します  *
 ***************************************/
static sensor_port_t
    touch_sensor    = EV3_PORT_1,
    color_sensor    = EV3_PORT_2,
    sonar_sensor    = EV3_PORT_3,
    gyro_sensor     = EV3_PORT_4;

static motor_port_t
    arm_motor       = EV3_PORT_A,
    left_motor      = EV3_PORT_C,
    right_motor     = EV3_PORT_B;


void change_LED_green();
void change_LED_red();
void device_init();
int get_touchsensor();
int get_reflectsensor();
int get_sonorsensor();
int get_gyrosensor();
int get_ambientsensor();
void encode_l_motor(int motorL);
void encode_r_motor(int motorR);
void encode_arm_motor(int motorArm);
int get_l_motor_ang();
int get_r_motor_ang();
int get_arm_motor_ang();
void stop_arm_motor();
void stop_wheel();
void motor_reset();
int detect_red_block();
int detect_blue();
int get_rgbsensor();
void stop_wheel_slowly();