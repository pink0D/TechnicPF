//
// Copyright (c) Dmitry Akulov. All rights reserved.
//
// Repository info:     https://github.com/pink0D/TechnicPF
// Contact information: pink0D.github@gmail.com
//
// Licensed under the MIT license. See LICENSE file in the project root for details.
//

#include <PS4BT.h>

#include <PFMotor.h>
#include <GeekServo.h>
#include <MKServo.h>

//
// define pins
//
#include "PinConfig.h"

//
// PlayStation style controls
//
#define INPUT_STEER         LeftHatX
#define INPUT_ACCELERATOR   R2
#define INPUT_BRAKE         L2
#define INPUT_REVERSE       TRIANGLE

#define INPUT_DEADZONE      10
#define INPUT_MAX           255

#define STEERING_MAX_ANGLE  90        // used to limit max servo rotation angle

//
// Controller setup
//
// for details about connecting Bluetooth devices to Arduino, please refer to
// examples https://github.com/felis/USB_Host_Shield_2.0
//
USB Usb;
BTD Btd(&Usb); 
PS4BT controller(&Btd, PAIR); // always start in pairing mode
//PS4BT controller(&Btd);     // not working...

//
// Technic motors setup
//
PFMotor motor;      // Motor A - PF Large motor
GeekServo servo;    // GeekServo - 3-wire servo
//MKServo servo;    // Motor B - MK Servo
//PFMotor servo;    // Motor B - PF Servo

bool reverse = false;

double input_to_steering(int input) {

  double limit = (((double)STEERING_MAX_ANGLE) / 90.0);

  if (input < INPUT_DEADZONE)
    return -limit; // full left

  if (input > INPUT_MAX - INPUT_DEADZONE)
    return limit;  // full right

  if (abs(INPUT_MAX / 2 - input) < INPUT_DEADZONE)
    return 0; // center

  return (2.0 * ( (double) input ) / ( (double) INPUT_MAX) - 1) * limit; // calculate
}

void setup() {
  Serial.begin(115200);
  
  motor.begin(MOTOR_A);
  servo.begin(GEEK_SERVO);
  //servo.begin(MOTOR_B); // MK
  //servo.begin(MOTOR_B, PWM_FIXED_3_POSITIONS);  // PF with 3-positions  (-90 / 0 / +90)
  //servo.begin(MOTOR_B, PWM_FIXED_15_POSITIONS); // PF with 15-positions (almost proportional)

  // init Bluetooth
  if (Usb.Init() == -1) {
    Serial.println("Bluetooth did not start");
    while (1); // halt
  }
  Serial.println("Startup OK");
}

void loop() {

  // get updates from controller
  Usb.Task();

  if (controller.connected()) {

    // get inputs from controller
    double accelerator = ((double) controller.getAnalogButton(INPUT_ACCELERATOR)) / ((double) INPUT_MAX);
    double steer = input_to_steering(controller.getAnalogHat(INPUT_STEER));
    bool brake = controller.getAnalogButton(INPUT_BRAKE) > INPUT_DEADZONE;
    if (controller.getButtonClick(INPUT_REVERSE))
      reverse = !reverse;
    if (reverse) 
      accelerator = -accelerator;

    // update motor outputs
    motor.update_motor(accelerator,brake); 
    servo.update_motor(steer);
  }
}
