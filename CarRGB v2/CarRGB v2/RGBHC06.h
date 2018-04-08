/* 
* HC06.h
*
* Created: 21.07.2017 12:45:40
* Author: Anatoly Tsirkunenko
*/


#ifndef __HC06_H__
#define __HC06_H__

#include <stdbool.h>
#include "USARTControl.h"


class HC06
{
public:
	bool received(void);
	void CleanString(void);
	uint8_t getRed(void);
	uint8_t getGreen(void);
	uint8_t getBlue(void);
	void Filter(void);
	HC06();
private:
	bool offFlag;
	char* string_prev;
	char rstring[4];
	char gstring[4];
	char bstring[4];
};

#endif
