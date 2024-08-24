//
// Copyright (c) Dmitry Akulov. All rights reserved.
//
// Repository info:     https://github.com/pink0D/TechnicPF
// Contact information: pink0D.github@gmail.com
//
// Licensed under the MIT license. See LICENSE file in the project root for details.
//

#ifndef _TechnicMotor_h
#define _TechnicMotor_h

class TechnicMotor {
public:
  // ctl_val must be within -1..1 range
  void update_motor(double ctl_val, bool brake = false) {
    if (ctl_val > 0) 
      update_output(ctl_val,0,brake);
    else 
      update_output(0,abs(ctl_val),brake);
  };
protected:
  // c1 and c2 must be within 0..1 range
  virtual void update_output(double new_c1, double new_c2, bool brake = false) {};
};

#endif
