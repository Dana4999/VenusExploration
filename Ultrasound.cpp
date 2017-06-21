#include <Servo.h>
#include <Arduino.h>
#include <Math.h>
#include "Defines.h"
#include "Ultrasound.h"

//Variable
long ultraTurn = 0;
bool ultraTurnRight = true;
bool scanning = false;

//Servo
extern Servo ultraSoundServo;

//Function to measure distance using the ultrasound sensor
long MeasureDistance()
{
  long duration;
  pinMode(9, OUTPUT);
  digitalWrite(9, LOW);
  delayMicroseconds(2);
  digitalWrite(9, HIGH);
  delayMicroseconds(5);
  digitalWrite(9, LOW);
  pinMode(9, INPUT);
  duration = pulseIn(9, HIGH);
  return duration / 58;
}

//Function to start scanning in front
void StartFrontScan()
{
  ultraTurn = 0;
  ultraTurnRight = true;
  scanning = true;
}

//Function to stop scanning in front
void StopFrontScan()
{
  scanning = false;
}

//Function that scans in front
long FrontScan()
{
  if(scanning)
  {
    //Move head to new angle
    int angle = ULTRATURNMIN + ((ULTRATURNSCALE / ULTRATURNANGLE) * ultraTurn);
    ultraSoundServo.write(angle);

    //Measure distance
    long distance = MeasureDistance();

    //Calculate new ultraTurn
    if(ultraTurnRight)
    {
      ultraTurn++;
      if(ultraTurn == ULTRATURNSCALE)
      {
        ultraTurnRight = false;
      }
    }
    else
    {
      ultraTurn--;
      if(ultraTurn == 0)
      {
        ultraTurnRight = true;
      }
    }
    return distance;
  }

  return 4999;
}

//Function that scans left
long ScanLeft()
{
  ultraSoundServo.write(ULTRALEFT);
  long distance = MeasureDistance();
  ultraSoundServo.write(ULTRAMIDDLE);  
  return distance;
}

//Function that scans right
long ScanRight()
{
  ultraSoundServo.write(ULTRARIGHT);
  long distance = MeasureDistance();
  ultraSoundServo.write(ULTRAMIDDLE);
  return distance;
}


