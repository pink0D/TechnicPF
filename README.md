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

# Basic usage
Motor driver 
code

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

