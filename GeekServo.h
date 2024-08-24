//
// Copyright (c) Dmitry Akulov. All rights reserved.
//
// Repository info:     https://github.com/pink0D/TechnicPF
// Contact information: pink0D.github@gmail.com
//
// Licensed under the MIT license. See LICENSE file in the project root for details.
//

#ifndef _GeekServo_h
#define _GeekServo_h

#include <Servo.h>
#include "TechnicMotor.h"

class GeekServo : public Servo, public TechnicMotor {
public:
  // default values for GeekServo 360 to steer between -90..+90
  void begin(int pin, int servo_min = 1000, int servo_max = 2000);

  // c1 and c2 must be within 0..1 range
  virtual void update_output(double new_c1, double new_c2, bool brake = false);

private:
  int servo_min;
  int servo_max;
};

#endif
