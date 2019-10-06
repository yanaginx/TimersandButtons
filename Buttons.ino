
#include "Buttons.h"
#include "timer.h"

 
void setup() 
{
    Serial.begin(9600);
    ledPinInitialize();
    timerInitialize();
}
 
void loop()
{
  // Main code loop
  // TODO: Put your regular (non-ISR) logic here
}
 
