//
// Copyright (c) Dmitry Akulov. All rights reserved.
//
// Repository info:     https://github.com/pink0D/TechnicPF
// Contact information: pink0D.github@gmail.com
//
// Licensed under the MIT license. See LICENSE file in the project root for details.
//

#include <Arduino.h>
#include "GeekServo.h"

void GeekServo::begin(int pin, int servo_min, int servo_max){
  this->servo_min = servo_min;
  this->servo_max = servo_max;

  attach(pin,servo_min,servo_max);
}

// output control signals to servo
void GeekServo::update_output(double new_c1, double new_c2, bool brake) {
  int st = (servo_max - servo_min) / 2;
  int us = (servo_min + servo_max) / 2 - st*new_c1 + st*new_c2;
  writeMicroseconds(us);
}
