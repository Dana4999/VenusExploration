#include <Servo.h>
#include "Driving.h"
#include "Ultrasound.h"
#include "Defines.h"

//Variables
extern volatile int leftTicks;
extern volatile int rightTicks;
extern int tickGoal;
bool ticksDone = false;
bool currentlyDriving = false;

//Servos
extern Servo leftServo;
extern Servo rightServo;

//Driving function
void Drive(int drivingDirection, int ticks)
{
  //Creating a new smart goal
  if (!currentlyDriving)
  {
    currentlyDriving = true;
    Stop();
    leftTicks = 0;
    rightTicks = 0;
    tickGoal = ticks;


    //Actual driving :)
    switch (drivingDirection)
    {
      case FORWARD:
        leftServo.write(0);
        rightServo.write(180);
        break;
      case RIGHT:
        leftServo.write(180);
        rightServo.write(180);
        break;
      case LEFT:
        leftServo.write(0);
        rightServo.write(0);
        break;
      case BACKWARD:
        leftServo.write(180);
        rightServo.write(0);
        break;
    }
  }

  //check if goal has been achieved
  //  CheckTicks();

  //Start scanning with the ultra sound sensor
  StartFrontScan();
}

//Stop function
void Stop()
{
  leftServo.write(90);
  rightServo.write(90);

  //Start scanning with the ultra sound sensor
  StopFrontScan();
}

//Function to check if the driving goal has been reached
bool CheckTicks()
{
  if (leftTicks >= tickGoal || rightTicks >= tickGoal)
  {
    Stop();
    currentlyDriving = false;
    return true;
  }
  return false;
}

