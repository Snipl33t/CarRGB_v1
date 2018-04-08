/* 
* RGB.cpp
*
* Created: 01.04.2018 16:34:34
* Author: Anatoly Tsirkunenko
*/


#include "RGB.h"
#include <stdbool.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <util/delay.h>

RGB::RGB()
{
	DDRB &= (0 << DDB1)|(0 << DDB2)|(0 << DDB3);
	TCCR1A |= (1 << COM1A1)|(1 << COM1B1)|(1 << WGM10);
	TCCR1B |= (1 << CS11)|(1 << WGM12);
	TCCR2 |= (1 << COM21)|(1 << WGM21)|(1 << WGM20)|(1 << CS21);
	OCR1A = 0; OCR1B = 0; OCR2 = 0;
}

void RGB::write(int red, int green, int blue)
{
	bool rflag = false;
	bool gflag = false;
	bool bflag = false;
	uint8_t red1 = red;
	uint8_t green1 = green;
	uint8_t blue1 = blue;
	if((red == 0) && (green == 0) && (blue == 0))
	{
		DDRB &= (0 << DDB1)|(0 << DDB2)|(0 << DDB3);
	}
	else DDRB |= (1 << DDB1)|(1 << DDB2)|(1 << DDB3);
	while(!(rflag && gflag && bflag))
	{
		if(red1 == OCR1A) rflag = true;
		if(!rflag)
		{
			if(red1 > OCR1A) OCR1A += 1;
			else OCR1A -= 1;
		}
		if(green1 == OCR1B) gflag = true;
		if(!gflag)
		{
			if(green1 > OCR1B) OCR1B += 1;
			else OCR1B -= 1;
		}
		if(blue1 == OCR2) bflag = true;
		if(!bflag)
		{
			if(blue1 > OCR2) OCR2 += 1;
			else  OCR2 -= 1;
		}
		_delay_ms(1);
	}
}