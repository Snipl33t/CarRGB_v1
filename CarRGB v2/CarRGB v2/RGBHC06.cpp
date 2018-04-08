/* 
* HC06.cpp
*
* Created: 21.07.2017 12:45:40
* Author: Anatoly Tsirkunenko
*/


#include "RGBHC06.h"
#include "USARTControl.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

HC06::HC06()
{
	offFlag = false;
}

void HC06::CleanString()
{
	USARTControl::instance.clearflag = true;
	USARTControl::instance.ClrStr();
}

void HC06::Filter()
{
	uint8_t r = 0;
	uint8_t g = 0;
	uint8_t b = 0;
	offFlag = false;
	char* string = USARTControl::instance.str;
	if(string[0] == 'O')
	{
		offFlag = true;
		goto endFilter;
	}
	for(uint8_t i = 0; i < 4; i++)
	{
		rstring[i] = 0;
		gstring[i] = 0;
		bstring[i] = 0;
	}
	while(string[r] != '.')
	{
		rstring[r] = string[r];
		++r;
	}
	while(string[g+r+1] != '.')
	{
		gstring[g] = string[g+r+1];
		++g;
	}
	while(string[b+g+r+2] != ')')
	{
		bstring[b] = string[b+g+r+2];
		++b;
	}
endFilter:
	USARTControl::instance.clearflag = true;
	USARTControl::instance.rxflag = false;
	USARTControl::instance.rxflag1 = false;
}

uint8_t HC06::getRed()
{
	uint8_t red;
	if(offFlag) red = 0;
	else red = atoi(rstring);
	return red;
}

uint8_t HC06::getGreen()
{
	uint8_t green;
	if(offFlag) green = 0;
	else green = atoi(gstring);
	return green;
}

uint8_t HC06::getBlue()
{
	uint8_t blue;
	if(offFlag) blue = 0;
	else blue = atoi(bstring);
	return blue;
}

bool HC06::received()
{
	return USARTControl::instance.rxflag1;
}