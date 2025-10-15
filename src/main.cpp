#include <Arduino.h>

#define POWER_STATUS_PIN 4
#define POWER_SWITCH_PIN 0

#define PUSH_DURATION 100 //ms
#define COOLDOWN 1000 //ms
bool powerStatus;

bool getPowerStatus()
{
  return digitalRead(POWER_STATUS_PIN);
}

void pushPowerSwitch()
{
  digitalWrite(POWER_SWITCH_PIN, HIGH);
  delay(PUSH_DURATION);
  digitalWrite(POWER_SWITCH_PIN, LOW);
}

void attemptPowerOn()
{
  pushPowerSwitch();
  delay(COOLDOWN); // cooldown between attempts
}

void setup()
{
  pinMode(POWER_STATUS_PIN, INPUT);
  pinMode(POWER_SWITCH_PIN, OUTPUT);
  delay(COOLDOWN); // wait
}

void loop()
{
  if (getPowerStatus())
  {
    // system is ON, do nothing, this section is not reachable normaly 
  }
  else
  {
    //  system is OFF
    while (!getPowerStatus()) // attempt pushing the putton until system starts up
    {
      attemptPowerOn();
    }
    while (1)
    {
      // this service runs only once only after power loss, full power cycle required for reset
    }
  }
}
