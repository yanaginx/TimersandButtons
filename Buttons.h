#ifndef _LED_H
#define _LED_H

#define LED1       10
#define LED2        9
#define LED3        8
#define LED4        7
#define LED5        6
#define LED6        5
#define LED7        4
#define LED8        3

#define RA5PinInc  13
#define RA5PinDec  12

void ledPinInitialize(void);
void ledToggle(uint8_t);

#endif
