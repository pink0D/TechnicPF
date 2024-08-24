//
// Copyright (c) Dmitry Akulov. All rights reserved.
//
// Repository info:     https://github.com/pink0D/TechnicPF
// Contact information: pink0D.github@gmail.com
//
// Licensed under the MIT license. See LICENSE file in the project root for details.
//

#ifndef _PFMotor_h
#define _PFMotor_h

#include "TechnicMotor.h"

#define MOTOR_DRIVER_TB6612FNG      0
#define MOTOR_DRIVER_L298N_MINI     1

#define PWM_PROPORTIONAL            0
#define PWM_FIXED_3_POSITIONS       1
#define PWM_FIXED_15_POSITIONS      2

struct PFMotorPinConfig {
  int driver_type;
  int pin_c1;
  int pin_c2;
  int pin_pwm;
  int pin_power_ctl;
};

class PFMotor : public TechnicMotor {
public:
  void begin (PFMotorPinConfig pin_config, int pwm_type = PWM_PROPORTIONAL);

  void set_pwm_type(int pwm_type);
  void power_on();
  void power_off();

protected:
  // c1 and c2 must be within 0..1 range
  virtual void update_output(double new_c1, double new_c2, bool brake = false);

private:
  int driver_type;
  int pwm_type = PWM_PROPORTIONAL;
  int pin_c1;
  int pin_c2;
  int pin_pwm;
  int pin_power_ctl;

  void output_pwm_TB6612FNG(double c1, double c2, bool brake);
  void output_pwm_L298N_mini(double c1, double c2, bool brake);

  double convert_pwm_3(double c);
  double convert_pwm_15(double c);
};

#endif
