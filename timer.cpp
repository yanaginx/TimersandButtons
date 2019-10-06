#include <Arduino.h>
#include <TimerOne.h>
#include "projectHeader.h"
#include "timer.h"
#include "Buttons.h"

uint8_t fbutton = 0;  
uint8_t fbuttonholdfirst = 0;
uint8_t fbuttonholdsecond = 0;
uint8_t count1 = 0;
uint8_t count2 = 0;
uint8_t triggerValue = ((HOLDTWO - HOLDONE)/AUTOONE)-1;
uint8_t triggerCounting = 0;
uint8_t count3 = 0;
uint8_t ledValue = 0;

void Readbutton();
void ResetValue ();
void Decrease(uint8_t);
void Increase(uint8_t);

void timerInitialize(){
    Timer1.initialize(TIMER_INTERRUPT_PERIOD); // set a timer of length 10000 microseconds (or 10 milliseconds)
    Timer1.attachInterrupt(Readbutton); // attach the service routine here: ---> after 10 milliseconds timer1 will call the '' function
}

/// --------------------------
/// Custom ISR Timer Routine
/// --------------------------
void Readbutton(void) {
  uint8_t RA5Inc = digitalRead(RA5PinInc);
  uint8_t RA5Dec = digitalRead(RA5PinDec);
  Serial.print(RA5Inc);
  Serial.print(' ');
  Serial.print(ledValue);
  Serial.print(' ');
  Serial.print(count1);
  Serial.print(' ');
  Serial.print(count2);
  Serial.print(' ');
  Serial.print(count3);
  Serial.print(' ');
  Serial.print(triggerValue);
  Serial.print(' ');
  Serial.println(triggerCounting);
  //Those only to check if the value counted correctly, you can remove if needed
  if (RA5Inc == 0 && RA5Dec == 1) Increase(RA5Inc); //increase the value when the increase button is pressed or holded
  else if (RA5Dec == 0 && RA5Inc == 1) Decrease(RA5Dec); //decrease the value when the decrease button is pressed or holded
  else Increase(RA5Inc); //increase button has high priority 
}

void Increase (uint8_t input){
  if (input == 0) {
    fbutton = 1;
    count1++;
    if (count1 <= 1) {
      ledValue = ledValue + 1;
      ledToggle(ledValue);
    } //if the button isn't being hold, increase only 1 value per read
    else {
      if (count1 >= HOLDONE){
        fbuttonholdfirst = 1; 
        count2++; 
        //button is hold longer than the HOLDONE period
        if (count2 >= AUTOONE && fbuttonholdfirst == 1){ 
          count2 = 0;
          count1 = HOLDONE;
          triggerCounting++;
          ledValue = ledValue + 1;
          ledToggle(ledValue);
        } //increase the Value at the speed of AUTOONE between the HOLDONE and HOLDTWO periods
          if (triggerCounting == triggerValue) {
            fbuttonholdfirst = 0;
            fbuttonholdsecond = 1;
            count3++;
            if (count3 >= AUTOTWO && fbuttonholdsecond == 1) {
              count3 = 0;
              count2 = 0;
              count1 = HOLDONE;
              ledValue = ledValue + 1;
              ledToggle(ledValue);
            } //increase the Value at the speed of AUTOTWO after HOLDTWO period
          }
        }
      }
    }
  else {
    fbutton = 0;  
    fbuttonholdfirst = 0;
    fbuttonholdsecond = 0;
    count1 = 0;
    count2 = 0;
    count3 = 0;
    triggerCounting = 0;
  } //reset the values upon release the button
}

void Decrease (uint8_t input){
  if (input == 0) {
    fbutton = 1;
    count1++;
    if (count1 <= 1) {
      ledValue = ledValue - 1;
      ledToggle(ledValue);
    } //if the button isn't being hold, decrease only 1 value per read
    else {
      if (count1 >= HOLDONE){
        fbuttonholdfirst = 1;
        count2++;
        //button is hold longer than the HOLDONE period
        if (count2 >= AUTOONE && fbuttonholdfirst == 1){
          count2 = 0;
          count1 = HOLDONE;
          triggerCounting++;
          ledValue = ledValue - 1;
          ledToggle(ledValue);
        } //increase the Value at the speed of AUTOONE between the HOLDONE and HOLDTWO periods
          if (triggerCounting == triggerValue) {
            fbuttonholdfirst = 0;
            fbuttonholdsecond = 1;
            count3++;
            if (count3 >= AUTOTWO && fbuttonholdsecond == 1) {
              count3 = 0;
              count2 = 0;
              count1 = HOLDONE;
              ledValue = ledValue - 1;
              ledToggle(ledValue);
            } //increase the Value at the speed of AUTOTWO after HOLDTWO period
          }
        }
      }
    }
  else {
    fbutton = 0;  
    fbuttonholdfirst = 0;
    fbuttonholdsecond = 0;
    triggerCounting = 0;
    count1 = 0;
    count2 = 0;
    count3 = 0;
  } //reset the values upon release the button
}
