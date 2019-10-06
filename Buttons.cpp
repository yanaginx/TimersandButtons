#include <Arduino.h>
#include "Buttons.h"
#include "projectHeader.h"


void ledPinInitialize(void){
	pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(LED5, OUTPUT);
  pinMode(LED6, OUTPUT);
  pinMode(LED7, OUTPUT);
  pinMode(LED8, OUTPUT);
	pinMode(RA5PinInc, INPUT_PULLUP);
  pinMode(RA5PinDec, INPUT_PULLUP);
  //assigning pins
}	

void ledToggle(uint8_t value){
  digitalWrite(LED8, (value & 1));
  digitalWrite(LED7, (value & 2));
  digitalWrite(LED6, (value & 4));
  digitalWrite(LED5, (value & 8));
  digitalWrite(LED4, (value & 16));
  digitalWrite(LED3, (value & 32));
  digitalWrite(LED2, (value & 64));
  digitalWrite(LED1, (value & 128));
  //toggle the led according to the value being sent to
}
