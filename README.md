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

Add the following code to your sketch:

```CPP
// library includes
#include <PFMotor.h>

// default pins
#include <PinConfig.h>

// if your installation is using different pinout, copy the default config to your project and redefine pins
// #include "PinConfig.h"

// define motor instance
PFMotor motor;

void setup() {
...
motor.begin(MOTOR_A);

// when using original PF motors, this option is recommended both for Servo and M/L/XL motors
// motor.begin(MOTOR_A, PWM_FIXED_15_POSITIONS); // PF with 15-positions (almost proportional)

// when using PF-compatible servo-motor, this option is recommended to avoid fluttering and power drain issues
// motor.begin(MOTOR_A, PWM_FIXED_3_POSITIONS);  // PF with 3-positions  (-90 / 0 / +90)

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
GeekServo is a standard 3-wire Servo with Technic bricks compatible housing. By specification, GeekServo has 3.3V to 6V operating voltage, so you will need a voltage regulator. Unofficially, GeekServo can be powered directly with 2S (7.4V) LiPo battery **(but use this setup at your own risk)**. 

![GeekServo!](https://raw.githubusercontent.com/pink0D/TechnicPF/main/wiring/geek_servo.png "GeekServo")

Code:
```CPP
// library includes
#include <GeekServo.h>

// default pins
#include <PinConfig.h>

// if your installation is using different pinout, copy the default config to your project and redefine pins
// #include "PinConfig.h"

// define motor instance
GeekServo servo;

void setup() {
...
// basic setup for a servo with 1000..2000 microseconds signals for -90..+90 rotation
servo.begin(GEEK_SERVO);

// GeekServo 360 supports wider range: 500..2500 microsecdons for -180..+180 rotation
// servo.begin(GEEK_SERVO,500,2500);
...
}

void loop() {
...
// any value in -1.0 .. +1.0 range
// positive/negative values set rotation direction.
// for a servo: 1.0 = maximum rotation, 0.5 = half rotation, 0 = zero position, -1.0 = maximum rotation in other direction
double rotation = 1.0; 
servo.update_motor(rotation); 
...
}
```

# Mould King Servo
Mould King Servos by default have only 3 fixed positions (-90, 0 and +90 rotation) when connected to control hubs. However, by sending a correct PWM signal, it is possible to make it rotate in a proportional way. There are also some side effects, including motor fluttering and hence significant power drain. This library provides a solution for proportional control of Mould King Servo Motor:

- Sending correct PWM signals to MK Servo
- Disconnecting power supply from the motor when it does not need to rotate, and connecting the power again before moving to a new position

To achive this, the hardware setup contatins N-channel MOSFETs, alogn with some resistors (100 Ohm and 10 kOhm). You can choose any N-channel MOSFET that can be driven by 3.3V logic. To reduce soldering, you can use power control circuit just for one of the motor, and connect GND pin of the second motor directly to PCB's GND.

More details about this solution in [my video on Youtube](https://www.youtube.com/watch?v=5rQFQ2EFzqE)

![MKServo!](https://raw.githubusercontent.com/pink0D/TechnicPF/main/wiring/mould_king_servo.png "MKServo")

Code:
```CPP
// library includes
#include <MKServo.h>

// default pins
#include <PinConfig.h>

// if your installation is using different pinout, copy the default config to your project and redefine pins
// #include "PinConfig.h"

// define motor instance - MKServo class contain special logic for proportional control
MKServo servo;

void setup() {
...
// MKServo initialization
servo.begin(MOTOR_A);
...
}

void loop() {
...
// any value in -1.0 .. +1.0 range
// positive/negative values set rotation direction.
// for a servo: 1.0 = maximum rotation, 0.5 = half rotation, 0 = zero position, -1.0 = maximum rotation in other direction
double rotation = 1.0; 
servo.update_motor(rotation); 
...
}
```

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

