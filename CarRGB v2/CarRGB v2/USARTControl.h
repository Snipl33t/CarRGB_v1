/* 
* USARTControl.h
*
* Created: 24.07.2017 9:26:12
* Author: Anatoly Tsirkunenko
*/


#ifndef __USARTCONTROL_H__
#define __USARTCONTROL_H__
#include <stdbool.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
//ISR(USART_RXC_vect);

class USARTControl
{
public:
	static USARTControl instance;
	USARTControl();
	bool clearflag;
	void DataReceived(void);
	void write(char *);
	void ClrStr(void);
	volatile uint8_t buffer;
	uint8_t count;
	uint8_t gcount;
	uint8_t bcount;
	bool rxflag;
	bool rxflag1;
	bool vectflag;
	char redstr[3];
	char greenstr[3];
	char bluestr[3];
	char str[32];
	bool redflag;
	bool greenflag;
	bool blueflag;
	int getRed(void);
	int getGreen(void);
	int getBlue(void);
	int red;
	int green;
	int blue;
private:
	void sendChar(uint8_t);
};

#endif
