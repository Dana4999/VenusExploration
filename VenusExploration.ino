#include <EnableInterrupt.h>
#include <Servo.h>
#include "Driving.h"
#include "Ultrasound.h"
#include "Defines.h"

//Variables
volatile int leftTicks;
volatile int rightTicks;
int tickGoal;

//Servos
Servo leftServo;
Servo rightServo;
Servo ultraSoundServo;

void setup()
{
  Serial.begin(9600);
  
  //Pin setup
  pinMode(7, INPUT_PULLUP);       //Left encoder
  pinMode(8, INPUT_PULLUP);       //Right encoder

  //Interrupt setup
  enableInterrupt(7, countLeftTicks, CHANGE);
  enableInterrupt(8, countRightTicks, CHANGE);

  //Servo setup
  leftServo.attach(12);
  rightServo.attach(13);
  ultraSoundServo.attach(11);

  ultraSoundServo.write(ULTRAMIDDLE);
  Stop();

}

void loop()
{
  //Always loop these functions
//  CheckTicks();
//  FrontScan();

  //The actual algorithm is here
  //TODO
  
  Drive(FORWARD, 8);
  if(CheckTicks())
  {
    Drive(RIGHT, 7);
  }
  
  

}

void countLeftTicks()
{
  leftTicks++;
  Serial.println("Left tick");
}

void countRightTicks()
{
  rightTicks++;
  Serial.println("Right tick");
}

