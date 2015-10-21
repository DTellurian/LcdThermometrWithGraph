/*
 * BaseLcdControl.h
 *
 * Created: 13.02.2015 16:55:13
 *  Author: Mihalych
 */ 


#ifndef BASELCDCONTROL_H_
#define BASELCDCONTROL_H_
//---------------------------------------------------------------------------

#include "LcdController.h"
//---------------------------------------------------------------------------

class BaseLcdControl
{
	public:
		BaseLcdControl(LcdController* lcdControllerPtr, uint8_t x, uint8_t y, uint8_t width, uint8_t height);				
		
		char* GetBufferPointerToWrite(uint8_t innerControlRowIndex = 0);
		void Clear(void);
		
		void CopyToLcdController(void);
	protected:
			uint8_t x;
			uint8_t y;
			uint8_t width;
			uint8_t height;
			
			Lcd* GetLcdPtr(void);
	private:
		BaseLcdControl(void);
		BaseLcdControl(const BaseLcdControl&);
		
		LcdController* lcdControllerPtr;
		char** controllBufferToWrite;
		//char controllBufferToWrite[10][10];
		
		
};
//---------------------------------------------------------------------------
#endif /* BASELCDCONTROL_H_ */