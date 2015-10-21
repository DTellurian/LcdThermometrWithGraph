/*
 * LedController.h
 *
 * Created: 12.02.2015 13:31:02
 *  Author: Mihalych
 */ 


#ifndef LCDCONTROLLER_H_
#define LCDCONTROLLER_H_
//---------------------------------------------------------------------------

#include "LcdControllerDefines.h"
#include "Lcd.h"
//---------------------------------------------------------------------------

using namespace LcdNamespace;

class LcdController
{
	friend class BaseLcdControl;
	
	public:
		LcdController(Lcd* lcdPtr);
		
		void Redraw(uint8_t forceRedraw = 0);
	protected:	
		
		
	private:
		LcdController(void);
		LcdController(const LcdController&);
		
		char bufferedtState[LCD_ROWS_COUNT][LCD_DIGITS_COUNT] = {{0},{0}};
		char currentState[LCD_ROWS_COUNT][LCD_DIGITS_COUNT] = {{0},{0}};
		
		Lcd* lcdPtr;
};
//---------------------------------------------------------------------------
#endif /* LCDCONTROLLER_H_ */