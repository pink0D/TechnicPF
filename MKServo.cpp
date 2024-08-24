//
// Copyright (c) Dmitry Akulov. All rights reserved.
//
// Repository info:     https://github.com/pink0D/TechnicPF
// Contact information: pink0D.github@gmail.com
//
// Licensed under the MIT license. See LICENSE file in the project root for details.
//

#include <Arduino.h>
#include "MKServo.h"

#define DEBUG

#ifdef DEBUG
  #define DEBUG_PRINT(x)    Serial.print (x)
  #define DEBUG_PRINTLN(x)  Serial.println (x)
#else
  #define DEBUG_PRINT(x)
  #define DEBUG_PRINTLN(x) 
#endif

// output control signals to servo
void MKServo::update_output(double new_c1, double new_c2, bool brake) {

  double delta1 = abs(c1 - new_c1);
  double delta2 = abs(c2 - new_c2);

  unsigned long time = millis();

  // check if input signal from HUB has been changed
  if ( (delta1 > DELTA_C) || (delta2 > DELTA_C) ) { 
    // give servo some time to rotate
    servoTimeLimit = time + SERVO_ROTATE_TIME_MILLIS;
    power_on();   // power on servo

    DEBUG_PRINT("rotate");
    DEBUG_PRINT(" new C1 = "); DEBUG_PRINT(new_c1);
    DEBUG_PRINT(" new C2 = "); DEBUG_PRINTLN(new_c2);

    // servo sometimes can't return directly to zero position (usually after sleep)
    if ( new_c1 + new_c2 < DELTA_C ) { // if new position should be ZERO...
      
      DEBUG_PRINT("rotate 1/2 after sleep");
      DEBUG_PRINT(" C1 / 2 = "); DEBUG_PRINT(c1 / 2);
      DEBUG_PRINT(" C2 / 2 = "); DEBUG_PRINTLN(c2 / 2);

      // first move to 1/2 of last known position 
      PFMotor::update_output(c1 / 2, c2 / 2);
      // give servo some time
      delay(20);
      // even more time if servo was powered off
      if (servo_power_status == 0)
        delay(40);
      // then finally return to zero position
      PFMotor::update_output(0, 0);
    }

    // update signal for servo
    PFMotor::update_output(new_c1,new_c2);
    servo_power_status = 1;

    c1 = new_c1;
    c2 = new_c2;

  }

  // power off servo after time limit - this is needed only in intermidiate positions
  if ((time > servoTimeLimit) && (c1 < 1.0) && (c2 < 1.0) && (c1 + c2 > 0))  
  {
    power_off(); // power off
    
    if (servo_power_status == 1) 
      DEBUG_PRINTLN("sleep");

    servo_power_status = 0;
  }
  else { // default to power on
    power_on();   
    servo_power_status = 1;
  }
}
