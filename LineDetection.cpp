#include <Arduino.h>
#include "LineDetection.h"
#include "Driving.h"
#include "Defines.h"

//Variables
int buffer1;
boolean name123;             //check again
int analogThreshold = 100;
int sensorPin;
int turnSide;
int sideSensor;

//Functions
void AvoidTape(int sensorSide)
{
  Stop();
  switch (sensorSide)
  {
    case LINELEFT:
      {
        sensorPin = A3;
        turnSide = RIGHT;
      }
      break;
    case LINERIGHT:
      {
        sensorPin = A2;
        turnSide = LEFT;
      }
      break;
  }

  for (int i = 0; i < 10; i++)
  {
    buffer1 = buffer1 + analogRead(sensorPin);
  }

  if (buffer1 / 10 < analogThreshold)
  {
    sideSensor = digitalRead(sensorPin);
    if (sideSensor == LOW)
    {
      Drive(BACKWARD, 14);
    }
    else
    {
      Drive(turnSide, 7);
    }
  }
}


