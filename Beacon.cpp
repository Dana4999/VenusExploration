#include <Servo.h>
#include "Driving.h"
#include "Ultrasound.h"
#include "Defines.h"
#include <Arduino.h>

//All the turnings left and right need to be optimised for the delay by ticks
//We might make them dependend on i for optimum performance

extern Servo ultraSoundServo;

void Beacon()
{
  int front;
  int back;
  int found = 0;
  front = analogRead(FRONTBEACONSENSOR);
  back = analogRead(BACKBEACONSENSOR);
  if (front >= BEACONUPPERTHRESHOLD) {
    return;

  }
  else if (front >= BEACONLOWERTHRESHOLD)
  { //drive straight
    while (analogRead(FRONTBEACONSENSOR) >= BEACONLOWERTHRESHOLD && analogRead(FRONTBEACONSENSOR) < BEACONUPPERTHRESHOLD)
    {
      Drive(FORWARD, 8);
    }
    Stop();
  }
  else if (back >= BEACONLOWERTHRESHOLD)
  { //turn robot around
    Drive(RIGHT, 10); //Should be turning 180 degrees around
    Stop();
  }
  else
  { //turn servo and check
    for (int i = 0; i < 180; i = i + 10)
    {
      delay(100);
      ultraSoundServo.write(i);
      front = analogRead(FRONTBEACONSENSOR);
      back = analogRead(BACKBEACONSENSOR);

      if ((front >= BEACONLOWERTHRESHOLD || back >= BEACONLOWERTHRESHOLD) && front < BEACONUPPERTHRESHOLD)
      { //turn to the angle
        if (i == 90 && front >= BEACONLOWERTHRESHOLD)
        {
          Beacon();
        }
        else if (i == 90 && back >= BEACONLOWERTHRESHOLD)
        {
          Drive(RIGHT, 1); //make it dependend on i ----------------------------------------------------------------------------
          Drive(FORWARD, 2);
          Stop();
        }
        else if (i < 90 && front >= BEACONLOWERTHRESHOLD)
        { //front pointed to the left
          Drive(RIGHT, 1);
          Drive(FORWARD, 2);
          Stop();
          found = 1;
        }
        else if (i < 90 && back >= BEACONLOWERTHRESHOLD)
        {
          Drive(LEFT, 8);; //we're going to need to turn more than 90 degrees left
          Drive(FORWARD, 2);
          Stop();
          found = 1;
        }
        else if (i > 90 && front >= BEACONLOWERTHRESHOLD)
        { //front pointed to the right
          Drive(LEFT, 2);
          Drive(FORWARD, 2);
          Stop();
          found = 1;
        }
        else if (i > 90 && back >= BEACONLOWERTHRESHOLD)
        {
          Drive(RIGHT, 2); //we're going to need to turn more than 90 degrees left
          Drive(FORWARD, 2);
          Stop();
          found = 1;
        }
      }
    }
  }
  if (found == 0)
  { //drive the robot around and check again
    Drive(FORWARD, 2);
    Stop();
  }
  ultraSoundServo.write(90);
  Beacon();
}
