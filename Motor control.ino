#include <Arduino.h>
#include <Esp.h>

#define enable 12
#define xDir 14
#define xStep 17

#define yDir 27
#define yStep 25

int steps = 200;

void step(boolean dir, boolean dir2, byte dirPin, byte dirPin2, byte stepperPin, byte stepperPin2, int steps) 
{
  digitalWrite(dirPin, dir);
  digitalWrite(dirPin2, dir2);
  delay(100);
  for (int i = 0; i < steps; i++) 
  {
    digitalWrite(stepperPin, HIGH);
    digitalWrite(stepperPin2, HIGH);
    delayMicroseconds(20);
   
    digitalWrite(stepperPin, LOW);
    digitalWrite(stepperPin2, LOW);
    delayMicroseconds(20);
  }
}
void setup()
{
   pinMode(xDir, OUTPUT);
   pinMode(xStep, OUTPUT);
   pinMode(yDir, OUTPUT);
   pinMode(yStep, OUTPUT);
   
   pinMode(enable, OUTPUT);
   digitalWrite(enable, LOW); 
}

void loop() 
{
  step(false, true, xDir, yDir, xStep, yStep, 26600);
  delay(1000);
  step(true, false, xDir, yDir, xStep, yStep, 26600);
  delay(1000);
}