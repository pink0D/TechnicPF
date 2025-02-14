# Important notice
This example is for demonstration purposes only. 
**The example hardware and the library itself DO NOT INCLUDE any kind of battery discharge protection.** 
Since electric motors consume quite a lot of power, this can lead to permament damage to Li-ion/LiPo batteries if there's no such protection. 
**For a real application please consider adding discharge control or use batteries with integrated protection curcuit.**

# Bluetooth gamepad controller example
[Demo video on Youtube](https://www.youtube.com/watch?v=hfu11bIr1LA)

The example project demostrates how to use the library and control Technic motors with a Bluetooth gamepad.
Components required:
- Arduino Pro Mini 3.3V
- Mini USB Host Shield 3.3V
- USB Bluetooth 4.0 dongle
- Bluetooth gamepad
- TB6612FNG motor driver
- LM7805 voltage regulator (optional for GeekServo)
- IRLB3034 or similar N-channel MOSFET + 100 Ohm + 10kOhm resistors (needed only for Mould King Servo proportional control)
- 7.4V LiPo battery

To reduce soldering time, you can:
- exclude LM7805 if you do not plan to use the GeekServo (or if you will use direct 7.4V power supply for it)
- include only one power control circuit for PF motors or even connect PF motors directly to PCB's GND if you do not need proportional control fo Mould King Servos

More examples for other Bluetooth gamepads are available in [USB_Host_Shield_2.0 library](https://github.com/felis/USB_Host_Shield_2.0)

![Full version!](https://raw.githubusercontent.com/pink0D/TechnicPF/main/wiring/full_version.png "Full version")

```CPP
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
  //servo.begin(MOTOR_B); // MK Servo with proportional control
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
```
