/*
 * TemperatureControl.h
 *
 * Created: 26.02.2015 16:42:06
 *  Author: Mihalych
 */ 


#ifndef TEMPERATURECONTROL_H_
#define TEMPERATURECONTROL_H_
//---------------------------------------------------------------------------

#include "BaseLcdControl.h"
//---------------------------------------------------------------------------

class TemperatureControl : public BaseLcdControl
{
	public:
		TemperatureControl(LcdController* lcdControllerPtr, uint8_t x, uint8_t y);
		
		void SetTemperature(uint16_t temperature);
	private:	
};
//---------------------------------------------------------------------------
#endif /* TEMPERATURECONTROL_H_ */