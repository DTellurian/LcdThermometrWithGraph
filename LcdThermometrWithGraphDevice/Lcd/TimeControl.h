/*
 * TimeControl.h
 *
 * Created: 03.03.2015 17:41:38
 *  Author: Mihalych
 */ 


#ifndef TIMECONTROL_H_
#define TIMECONTROL_H_
//---------------------------------------------------------------------------

#include "BaseLcdControl.h"
#include "../BaseTypes/CFTime.h"
//---------------------------------------------------------------------------

class TimeControl : public BaseLcdControl
{
	public:
		TimeControl(LcdController* lcdControllerPtr, uint8_t x, uint8_t y);
	
		void SetTime(CFTime& time);		
	private:
};
//---------------------------------------------------------------------------
#endif /* TIMECONTROL_H_ */