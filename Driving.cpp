#include <Servo.h>
#include "Driving.h"
#include "Defines.h"

//Variables
extern volatile int leftTicks;
extern volatile int rightTicks;
int tickGoal;

//Servos
extern Servo leftServo;
extern Servo rightServo;

//Driving function
void Drive(int drivingDirection, int ticks)
{
  Stop();

  //Creating a new smart goal 
  leftTicks = 0;
  rightTicks = 0;
  tickGoal = ticks;

  //Actual driving :)
  switch(drivingDirection)
  {
    case FORWARD:
      leftServo.write(180);
      rightServo.write(0);
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
      leftServo.write(0);
      rightServo.write(180);
    break;  
  }
}

//Stop function
void Stop()
{
  leftServo.write(90);
  rightServo.write(90);
}

//Function to check if the driving goal has been reached
void CheckTicks()
{    
  if(leftTicks >= tickGoal || rightTicks >= tickGoal)
  {
    Stop();  
  }
}

