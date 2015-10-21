/*
 * SimpleLcdTermometer.cpp
 *
 * Created: 06.02.2015 23:00:52
 *  Author: Mihalych
 */ 
//---------------------------------------------------------------------------

#include "DeviceConfiguration.h"

#include <avr/io.h>
#include <util/delay.h>

#include "Device.h"
#include "Lcd/BaseLcdControl.h"
#include <stdio.h>
#include "BaseTypes/DateTime.h"
//---------------------------------------------------------------------------

#include "TemperatureHolder.h"


int main(void)
{		
	Device::Initialize();
	
	int16_t sensor0Vaules[15] = {-101, -117, -141, -123, -99, -83, -62, -42, -17, 1, 23, 37, 17, 1, 23};
	//int16_t sensor0Vaules[15] = {-83, -62, -42, -17, 1, 23, 37, 17, 1, 23, -101, -117, -141, -123, -99};
	
	//for(uint8_t testCounter = 0; testCounter < 15; testCounter++)
		//TemperatureHolder::ProceedMeasurement(sensor0Vaules[testCounter], 1);

	//int16_t restored[15] = {0};
//
	//TemperatureHolder::ReadMeasurements(restored, 1);
//
	//int16_t minValue = 0;
	//int16_t maxValue = 0;
	//
	//uint8_t maxValueIndex;
	//uint8_t minValueIndex;
	//
	//int8_t roundData[15] = {0};
	//uint8_t grapgData[15] = {0};	
	//
	//TemperatureHolder::RoundMeasurements(restored, roundData, minValue, maxValue, maxValueIndex, minValueIndex);
	//TemperatureHolder::CreateGraphData(roundData, grapgData, minValue, maxValue, maxValueIndex, minValueIndex);
	
	uint64_t nextMeasurementTime = 0;
	
    while(1)
    {		
		//Device::timeControl.SetTime(DateTime::CurrentTime);
		
		if(DateTime::milliseconds > nextMeasurementTime)
		{
			nextMeasurementTime = DateTime::milliseconds + 1000;
			Device::MeasureAndSetScreen();									
			
			//TemperatureHolder::ReadMeasurements(restored, 1);
			//TemperatureHolder::RoundMeasurements(restored, roundData, minValue, maxValue, maxValueIndex, minValueIndex);
			//TemperatureHolder::CreateGraphData(roundData, grapgData, minValue, maxValue, maxValueIndex, minValueIndex);
			//Device::graph.SetData(grapgData);	
		}

		Device::RedrawLcd();		
    }
}
//---------------------------------------------------------------------------