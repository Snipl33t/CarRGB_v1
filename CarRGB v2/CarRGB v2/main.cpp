/*
 * CarRGB.cpp
 *
 * Created: 01.04.2018 15:25:55
 * Author : Anatoly Tsirkunenko
 */ 
#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include <stdlib.h>
#include "RGBHC06.h"
#include "RGB.h"
#include <stdbool.h>

HC06 hc06;
RGB rgb;

int main(void)
{
    while (1) 
    {
		if(hc06.received())
		{
			cli();
			hc06.Filter();
			rgb.write(hc06.getRed(), hc06.getGreen(), hc06.getBlue());
			_delay_ms(5);
			sei();
		}
		cli();
		while(!(UCSRA & (1 << UDRE)));
		sei();
		_delay_ms(500);
	}
}


