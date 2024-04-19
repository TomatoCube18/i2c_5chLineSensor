# i2c_5chLineSensor
coming soon

## Description
The TomatoCube i2C IR Line Sensor Module provides a very low-cost yet simple & reliable way for detecting visible path for your robot to follow. It comes with on-board calibration variable potentiometer to adjust the sensitivity of the sensor Module.

Each IR sensor elements comes with an emitter & receiver. The Emitter will constantly send out a beam of IR Light, and upon hitting a reflective surface (White/Reflective Material on the ground), the IR beam will be reflected back to the corresponding sensor's receiver. The Sensor module will return a 5-bits value corresponding to the reflected IR signal through the i2C Grove connection.

## Specification:
Sensor Module MCU/IC: Attiny1614 
Interface type: i2C interface
Range: 0.5cm to 3cm

The firmware of the sensor module set the i2c address of the i2C IR Line Sensor module at 0x17 (default).

## Instruction
* Connect the 5-Channel IR Line sensor to your Robot.
* Using the LEDs on the sensor board, calibrate the sensitivity using the on-board potential-meter.
* Test the code below to verify the correct functionality with an Arduino Uno board.
coming soon


