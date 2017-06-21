#include <Servo.h>
#include "Driving.h"
#include "Defines.h"
#include <Arduino.h>

extern Servo gripper_servo;

void grabRock(){
  gripper_servo.write(180);
  delay(500);
  Drive(FORWARD, 2);
  ///////////////////////////////////////////How to call drive forward with the number of ticks???
  delay(300);
  Stop();
  gripper_servo.write(95); //not 0 because pulling up the gripper too high would leave the sensor range of rock sensor
  delay(500);
 }

void releaseRock(){
 gripper_servo.write(160);
 delay(500);
 gripper_servo.write(0);
}
