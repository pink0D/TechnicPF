# About
TechnicPF is an Arduino library for controlling Power Functions motors. 

# Important information
The example included in this library is for demonstration purposes only. **The example hardware and the library itself DO NOT INCLUDE any kind of battery discharge protection.** Since electric motors consume quite a lot of power, this can lead to permament damage to Li-ion/LiPo batteries if there's no such protection. **For a real application please consider adding discharge control or use a batteries with integrated protection curcuit.**

# Supported motors
The library supports several types of motors:
- Original PF Motors (including proportional Servos)
- PF Simple motors (M/L/XL-motors)
- PF Servo Motors (which usually have only 3 positions: -90 / 0 / +90)
- Mould King Servo motors (which normally also have just 3 positions, however this library introduces support for fully proportional steering)
- GeekServo (Technic-compatible motors with 3-wire plug)

# Library istallation
Copy contents of this repo to *<Worspace folder>/libraries/TechnicPF* 

# Basic Power Functions motors
For basic use of Power Functions motors you will need:
- Arduino Board
- TB6612FNG motor driver
- 7.4V LiPo battery
- Any PF compatible motors

![Basic usage!](https://raw.githubusercontent.com/pink0D/TechnicPF/main/wiring/basic_usage.png "Basic usage")

Add the following code to your sketch

```CPP
// library includes
#include <PFMotor.h>

// default pins
#include <PinConfig.h>

// if your isntallation is using different pinout, copy the default config to your project and redefine pins
// #include "PinConfig.h"

// define motor instance
PFMotor motor;

void setup() {
...
motor.begin(MOTOR_A);

// when using original PF motors, this option is recommended both for Servo and M/L/XL motors
//motor.begin(MOTOR_A, PWM_FIXED_15_POSITIONS); // PF with 15-positions (almost proportional)

// when using PF-compatible servo-motor, this option is recommended to avoid fluttering and power drain issues
//motor.begin(MOTOR_A, PWM_FIXED_3_POSITIONS);  // PF with 3-positions  (-90 / 0 / +90)

...
}

void loop() {
...
// when needed, set motor rotation speed:
// any value in -1.0 .. +1.0 range, 1.0 = full speed, 0.5 = half speed, zero value (0.0) stops the motor
// positive/negative values set rotation direction.
// for a servo: 1.0 = 90 degree rotation, 0.5 = 45 degree rotation, 0 = zero position, -1.0 = -90 degree rotation
double speed_control = 1.0; 
bool brake = false; // set to true to brake the motor (the driver shorts motor brushes which results to a fast stop)
motor.update_motor(speed_control,brake); 
...
}
```

# GeekServo
LM7805 optional
code

# Mould King Servo
transistor (only 1)
code
PoC video


# Full example
The example project demostrates how to use the library and control Technic motors with a Bluetooth gamepad.
Components required:
- Arduino Pro Mini 3.3V
- Mini USB Host Shield 3.3V + USB Bluetooth 4.0 dongle + Bluetooth gamepad
- TB6612FNG motor driver
- LM7805 voltage regulator (optional for GeekServo)
- IRLB3034 or similar N-channel MOSFET + 100 Ohm + 10kOhm resistors (needed only for Mould King Servo proportional control)
- 7.4V LiPo battery

wiring

code

video

