#include <EnableInterrupt.h>
#include <Servo.h>
#include "Driving.h"
#include "Defines.h"

//Variables
volatile int leftTicks;
volatile int rightTicks;

//Servos
Servo leftServo;
Servo rightServo;

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

  Stop();
}

void loop()
{
  CheckTicks();
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

