/*
* USARTControl.cpp
*
* Created: 24.07.2017 9:26:12
* Author: Anatoly Tsirkunenko
*/


#include "USARTControl.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define F_CPU 8000000UL
#define BAUD 9600L
#define UBRRL_value ((F_CPU/(BAUD*16))-1)

USARTControl USARTControl::instance;

USARTControl::USARTControl()
{
	sei();
	UCSRB |= (1 << RXCIE)|(1 << TXEN)|(1 << RXEN);
	UCSRC |= (1 << URSEL) | (1 << UCSZ0) | (1 << UCSZ1);
	UBRRH = 0;
	UBRRL = UBRRL_value;

	clearflag = true;
	rxflag = false;
	rxflag1 = false;
	buffer = 0;
	ClrStr();
	count = 0;
}

void USARTControl::sendChar(uint8_t value)
{
	while(!(UCSRA & (1 << UDRE)));
	UDR = value;
}

void USARTControl::write(char transstr[])
{
	uint8_t i = 0;
	while(transstr[i] != '\0')
	{
		sendChar(transstr[i]);
		++i;
	}
}

void USARTControl::ClrStr()
{
	if(!rxflag)
	{
		if(clearflag)
		{
			for(count = 0; count < 32; ++count)
			{
				str[count] = 0;
			}
			clearflag = false;
			count = 0;
		}
	}
}

void USARTControl::DataReceived()
{
	cli();
	ClrStr();
	while(!(UCSRA & (1 <<RXC)));
	buffer = UDR;
	str[count] = buffer;
	++count;
 	buffer = 0;
	rxflag1 = true;
 	rxflag = true;
}

ISR(USART_RXC_vect)
{
	USARTControl::instance.DataReceived();
}