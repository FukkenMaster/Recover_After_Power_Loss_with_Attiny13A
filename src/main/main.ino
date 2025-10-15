#include <Arduino.h>

int sensorLedPin = 2;
int turnOnLedPin = 3;
int pwrSensorPin = 4;
int turnOnPin = 5;

bool isPwrLedOn = false;
bool isPwrSensorOn = false;

int afterTurnOffDelay = 6197;
int turnOnDelay = 4163;
int runningLoopDelay = 3231;

void turnOnOnce()
{
  while (digitalRead(pwrSensorPin) == false)
  {
    digitalWrite(turnOnPin, HIGH);
    digitalWrite(turnOnLedPin, HIGH);
    delay(100);
    digitalWrite(turnOnPin, LOW);
    digitalWrite(turnOnLedPin, LOW);
    delay(turnOnDelay);
  }
}

void setup()
{

  pinMode(pwrSensorPin, INPUT);
  pinMode(sensorLedPin, OUTPUT);
  pinMode(turnOnPin, OUTPUT);
  pinMode(turnOnLedPin, OUTPUT);
  delay(1000);
}

void loop()
{
  // read the status
  isPwrSensorOn = digitalRead(pwrSensorPin);

  if (isPwrSensorOn == false)
  {                // if false
    checkTurnOn(); // read internal flag
  }
  else
  {
    checkPwrLed();           // correct the status and indicator mismatch
    delay(runningLoopDelay); // wait
  }
}

void checkTurnOn()
{
  if (isPwrLedOn) // check internal flag
  {
    digitalWrite(sensorLedPin, LOW); // if true: turn off the LED
    isPwrLedOn = false;              // set flag_2 to false
    delay(afterTurnOffDelay);        // wait...
  }
  else
  {
    turnOnOnce();                     // if flase: attempt pushing the power button until it works
    digitalWrite(sensorLedPin, HIGH); // turn on the LED
    isPwrLedOn = true;                // set the flag_2 true
  }
}
void checkPwrLed() // correct the status and indicator mismatch
{
  if (isPwrLedOn == false)
  {
    digitalWrite(sensorLedPin, HIGH); // if flag_2 is false turn on the LED
    isPwrLedOn = true;                // set flag_2 to true
  }
}