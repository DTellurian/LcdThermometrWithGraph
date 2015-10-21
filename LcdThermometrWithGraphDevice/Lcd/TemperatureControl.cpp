/*
 * TemperatureControl.cpp
 *
 * Created: 26.02.2015 16:42:26
 *  Author: Mihalych
 */ 
//---------------------------------------------------------------------------

#include "../DS18B20Support/DS18B20.h"
#include "TemperatureControl.h"
#include <stdio.h>
//---------------------------------------------------------------------------

TemperatureControl::TemperatureControl(LcdController* lcdControllerPtr, uint8_t x, uint8_t y)
	:BaseLcdControl(lcdControllerPtr, x, y, 5, 1)
{
	
}
//---------------------------------------------------------------------------

void TemperatureControl::SetTemperature(uint16_t temperature)
{
	uint8_t isPositive = 0;
	uint8_t integralPart = 0;
	uint8_t fractionPart = 0;

	ConvertTemperatureMeasurement(temperature, isPositive, integralPart, fractionPart);
	
	char positiveChar = isPositive == 1 ? '+' : '-';
	
	char* buffer = GetBufferPointerToWrite();
	sprintf(buffer, "%.c%.d.%d", positiveChar, integralPart, fractionPart);
	
//	CopyToLcdController();
}
//---------------------------------------------------------------------------