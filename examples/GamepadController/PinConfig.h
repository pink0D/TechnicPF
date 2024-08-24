//
// Copyright (c) Dmitry Akulov. All rights reserved.
//
// Repository info:     https://github.com/pink0D/TechnicPF
// Contact information: pink0D.github@gmail.com
//
// Licensed under the MIT license. See LICENSE file in the project root for details.
//

#ifndef _PinConfig_h
#define _PinConfig_h

#include <PFMotor.h>

/*
Pro Mini Pins
PWM pins: 3, 5, 6, 9, 10, and 11 - 9,10,11 - used by SPI for USB Shield

2 
3 pwm 490Hz - geek servo control
4 
5 pwm 980Hz - motor A pwm
6 pwm 980Hz - motor B pwm
7 motor B power control
8 motor A power control
A0 motor A C2
A1 motor A C1
A2 motor B C1
A3 motor B C2
*/

#define MOTOR_A_DRIVER    MOTOR_DRIVER_TB6612FNG // MOTOR_DRIVER_TB6612FNG or MOTOR_DRIVER_L298N_MINI
#define MOTOR_A_C1        A1   
#define MOTOR_A_C2        A0   
#define MOTOR_A_PWM       5 // set to 0 if using L298N mini
#define MOTOR_A_POWERCTL  8 // set to 0 if the assembly does not contain power control transistors

#define MOTOR_B_DRIVER    MOTOR_DRIVER_TB6612FNG // MOTOR_DRIVER_TB6612FNG or MOTOR_DRIVER_L298N_MINI
#define MOTOR_B_C1        A2   
#define MOTOR_B_C2        A3   
#define MOTOR_B_PWM       6 // set to 0 if using L298N mini
#define MOTOR_B_POWERCTL  7 // set to 0 if the assembly does not contain power control transistors

#define MOTOR_A PFMotorPinConfig {MOTOR_A_DRIVER,MOTOR_A_C1,MOTOR_A_C2,MOTOR_A_PWM,MOTOR_A_POWERCTL}
#define MOTOR_B PFMotorPinConfig {MOTOR_B_DRIVER,MOTOR_B_C1,MOTOR_B_C2,MOTOR_B_PWM,MOTOR_B_POWERCTL}

#define GEEK_SERVO        3 // pin for controlling 3-wire servo

#endif
