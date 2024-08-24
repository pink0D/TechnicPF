//
// Copyright (c) Dmitry Akulov. All rights reserved.
//
// Repository info:     https://github.com/pink0D/TechnicPF
// Contact information: pink0D.github@gmail.com
//
// Licensed under the MIT license. See LICENSE file in the project root for details.
//

#include <Arduino.h>
#include "PFMotor.h"


void PFMotor::begin(PFMotorPinConfig pin_config, int pwm_type) {
  
  this->driver_type = pin_config.driver_type;
  this->pin_pwm = pin_config.pin_pwm;
  this->pin_c1 = pin_config.pin_c1;
  this->pin_c2 = pin_config.pin_c2;
  this->pin_power_ctl = pin_config.pin_power_ctl;

  pinMode(pin_c1, OUTPUT);
  digitalWrite(pin_c1, LOW);

  pinMode(pin_c2, OUTPUT);
  digitalWrite(pin_c2, LOW);
  
  if(pin_pwm > 0) {
    pinMode(pin_pwm, OUTPUT);
    digitalWrite(pin_pwm, LOW);
  }

  power_on();

  set_pwm_type(pwm_type);
}

void PFMotor::set_pwm_type(int pwm_type) {
  this->pwm_type = pwm_type;
}

void PFMotor::power_on() {
  if(pin_power_ctl > 0) {
    pinMode(pin_power_ctl, OUTPUT);
    digitalWrite(pin_power_ctl, HIGH);
  }
}

void PFMotor::power_off() {
  if(pin_power_ctl > 0) {
    pinMode(pin_power_ctl, OUTPUT);
    digitalWrite(pin_power_ctl, LOW);
  }
}

void PFMotor::output_pwm_TB6612FNG(double c1, double c2, bool brake) {
  if (brake) {
    digitalWrite(pin_c1, HIGH);
    digitalWrite(pin_c2, HIGH);
    return;
  }

  double out_pwm = 0;
  int out_c1 = LOW;
  int out_c2 = LOW;

  if(c1 > 0) {
    out_c1 = HIGH;
    out_pwm = c1;
  }

  if(c2 > 0) {
    out_c2 = HIGH;
    out_pwm = c2;
  }

  digitalWrite(pin_c1, out_c1);
  digitalWrite(pin_c2, out_c2);
  analogWrite(pin_pwm, out_pwm * 255);
}

void PFMotor::output_pwm_L298N_mini(double c1, double c2, bool brake) {
  
  if (brake) {
    digitalWrite(pin_c1, HIGH);
    digitalWrite(pin_c2, HIGH);
    return;
  }

  if (c1 > 0) {   
    analogWrite(pin_c1, c1 * 255);
  } else {
    digitalWrite(pin_c1, LOW);
  }

  if (c2 > 0) {   
    analogWrite(pin_c2, c2 * 255);
  } else {
    digitalWrite(pin_c2, LOW);     
  }
}

// update signal for motor
// c1 and c2 must be within 0..1 range
void PFMotor::update_output(double new_c1, double new_c2, bool brake) {

  if (new_c1 < 0) 
    new_c1 = 0;

  if (new_c2 < 0) 
    new_c2 = 0;

  if (new_c1 > 1) 
    new_c1 = 1;

  if (new_c2 > 1) 
    new_c2 = 1;

  if (pwm_type == PWM_FIXED_3_POSITIONS) {
    new_c1 = convert_pwm_3(new_c1);
    new_c2 = convert_pwm_3(new_c2);
  }

  if (pwm_type == PWM_FIXED_15_POSITIONS) {
    new_c1 = convert_pwm_15(new_c1);
    new_c2 = convert_pwm_15(new_c2);
  }

  if (driver_type == MOTOR_DRIVER_TB6612FNG)
    output_pwm_TB6612FNG(new_c1, new_c2, brake);

  if (driver_type == MOTOR_DRIVER_L298N_MINI)
    output_pwm_L298N_mini(new_c1, new_c2, brake);
}

double PFMotor::convert_pwm_3(double c){
  if (c > 0.25)
    return 1;

  return 0;
}

double PFMotor::convert_pwm_15(double c){
  // returned value * 255 should match fixed PWM byte values 0-66-97-128-162-194-225-255

  if (c > 0.88)
    return 1;

  if (c > 0.75)
    return 0.885;

  if (c > 0.62)
    return 0.762;

  if (c > 0.49)
    return 0.637;

  if (c > 0.36)
    return 0.505;

  if (c > 0.23)
    return 0.381;

  if (c > 0.10)
    return 0.261;

  return 0;
}