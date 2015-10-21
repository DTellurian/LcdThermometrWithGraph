/*
 * LedController.cpp
 *
 * Created: 12.02.2015 13:31:15
 *  Author: Mihalych
 */ 
//---------------------------------------------------------------------------

#include "LcdController.h"
//---------------------------------------------------------------------------

LcdController::LcdController(Lcd* lcdPtr)
{
	this->lcdPtr = lcdPtr;
}
//---------------------------------------------------------------------------

void LcdController::Redraw(uint8_t forceRedraw)
{	
	uint8_t previousRedrawFlag = 1;
	
	for(uint8_t y = 0; y < LCD_ROWS_COUNT; y++)
	{
		lcdPtr->LCD_Goto(0, y);
		
		for(uint8_t x = 0; x < LCD_DIGITS_COUNT; x++)
		{
			if(forceRedraw != 1 && currentState[y][x] == bufferedtState[y][x])
			{
				previousRedrawFlag = 0;
				continue;
			}						
			
			if(previousRedrawFlag != 1)
				lcdPtr->LCD_Goto(x, y);			
			
			if(bufferedtState[y][x] == 0)
				lcdPtr->LCD_WriteData(0x20);
			else
				lcdPtr->LCD_WriteData(bufferedtState[y][x]);
			
			currentState[y][x] = bufferedtState[y][x];
			previousRedrawFlag = 1;
		}
	}
}
//---------------------------------------------------------------------------