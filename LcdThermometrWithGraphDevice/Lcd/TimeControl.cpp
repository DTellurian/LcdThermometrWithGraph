/*
 * TimeControl.cpp
 *
 * Created: 03.03.2015 17:41:46
 *  Author: Mihalych
 */ 
//---------------------------------------------------------------------------

#include "TimeControl.h"
#include <stdio.h>
//---------------------------------------------------------------------------

TimeControl::TimeControl(LcdController* lcdControllerPtr, uint8_t x, uint8_t y)
	:BaseLcdControl(lcdControllerPtr, x, y, 8, 1)
{
	
}
//---------------------------------------------------------------------------

void TimeControl::SetTime(CFTime& time)
{
	char* buffer = GetBufferPointerToWrite();
	time.ToString(buffer);
	//sprintf(buffer, "%d:89:25");
	
	//CopyToLcdController();
}
//---------------------------------------------------------------------------