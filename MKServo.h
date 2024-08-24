//
// Copyright (c) Dmitry Akulov. All rights reserved.
//
// Repository info:     https://github.com/pink0D/TechnicPF
// Contact information: pink0D.github@gmail.com
//
// Licensed under the MIT license. See LICENSE file in the project root for details.
//

#ifndef _MKServo_h
#define _MKServo_h

#include "PFMotor.h"

// duration for powering servo motor - it should rotate within given timeout, then the power is turned off
#define SERVO_ROTATE_TIME_MILLIS 200 

// minimum change in C1/C2 signal that is sent to servo
#define DELTA_C 0.02  

class MKServo : public PFMotor{
protected:
  virtual void update_output(double new_c1, double new_c2, bool brake = false);

private:
  double c1 = 0;
  double c2 = 0;
  unsigned long servoTimeLimit = 0;
  int servo_power_status = 0;
};

#endif
