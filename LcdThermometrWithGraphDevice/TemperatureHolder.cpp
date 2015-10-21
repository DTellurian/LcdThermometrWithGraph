/*
 * TemperatureHolder.cpp
 *
 * Created: 05.03.2015 12:42:06
 *  Author: Mihalych
 */ 
//---------------------------------------------------------------------------

#include "TemperatureHolder.h"
#include "BaseTypes/EEPROM.h"
#include "BaseTypes/DateTime.h"
#include <stdlib.h>
//---------------------------------------------------------------------------



#define StartEEPROMIndex 4
#define MeasurementsCount 15
#define MeasurementsBufferSize (MeasurementsCount * 2)
#define MaxGraphYIndex 7

//---------------------------------------------------------------------------

TemperatureHolder::TemperatureHolder(uint8_t sensorIndex, uint64_t measurementPeriod)
{
	this->sensorIndex = sensorIndex;
	
	measurementsSumm = 0;
	measurementsCounter = 0;

	this->measurementPeriod = measurementPeriod;	
	nextMeasurementTime = 4000;
}
//---------------------------------------------------------------------------

uint8_t TemperatureHolder::ProceedMeasurement(int16_t temperature)
{
	uint8_t result = 0;
	
	measurementsSumm += temperature;
	measurementsCounter++;
	
	if(DateTime::milliseconds > nextMeasurementTime)	
	{
		WriteNextHoursValue(measurementsSumm / measurementsCounter, sensorIndex);
		
		measurementsCounter = 0;
		measurementsSumm = 0;
		
		nextMeasurementTime = DateTime::milliseconds + measurementPeriod;
		
		result = 1;
	}
	
	return result;
}
//---------------------------------------------------------------------------

void TemperatureHolder::WriteNextHoursValue(int16_t hourValue, uint8_t sensorIndex)
{
	uint8_t currentDeviceBufferStartIndex = StartEEPROMIndex + sensorIndex * MeasurementsBufferSize;	
	
	EEPROM::ShiftLeft(currentDeviceBufferStartIndex, MeasurementsBufferSize);
	EEPROM::ShiftLeft(currentDeviceBufferStartIndex, MeasurementsBufferSize);
	
	uint8_t leftPart = hourValue >> 8;
	uint8_t rightPart = hourValue << 8 >> 8;
	
	EEPROM::Write(currentDeviceBufferStartIndex + MeasurementsBufferSize - 2, leftPart);
	EEPROM::Write(currentDeviceBufferStartIndex + MeasurementsBufferSize - 1, rightPart);
}
//---------------------------------------------------------------------------

void TemperatureHolder::ReadMeasurements(int16_t *bufferPtr)
{
	//TODO:Не надо все времы вычитывать из EEPROM. Делать это один раз при загрузке устройства, потом хранить копию в памяти
	uint8_t currentDeviceBufferStartIndex = StartEEPROMIndex + sensorIndex * MeasurementsBufferSize;

	for(int i = 0; i < MeasurementsCount; i++)
	{	
		uint16_t leftPart = 0;
		uint16_t rightPart = 0;
		
		leftPart = EEPROM::Read(currentDeviceBufferStartIndex + i * 2);
		rightPart = EEPROM::Read(currentDeviceBufferStartIndex + i * 2 + 1);
		
		int16_t result = leftPart << 8;
		result |= rightPart;
		
		bufferPtr[i] = result;
	}
}
//---------------------------------------------------------------------------

void TemperatureHolder::RoundMeasurements(int16_t *deviceValue, int8_t *roundData, int16_t &minValue, int16_t &maxValue, uint8_t &maxValueIndex, uint8_t &minValueIndex)
{
	minValue = 900;
	maxValue = -273;
	
	for(int i = 0; i < MeasurementsCount; i++)
	{
		if(abs(deviceValue[i] % 10) <= 5)
			roundData[i] = deviceValue[i] / 10;
		else
		{
			roundData[i] = deviceValue[i] / 10;
			
			if(roundData[i] < 0)
				roundData[i] -= 1;
			else
				roundData[i] += 1;
		}
		
		if(roundData[i] > maxValue)
		{			
			maxValue = roundData[i];
			maxValueIndex = i;
		}
			
		if(roundData[i] < minValue)
		{
			minValue = roundData[i];
			minValueIndex = i;
		}
	}
}
//---------------------------------------------------------------------------

void TemperatureHolder::CreateGraphData(int8_t *roundData, uint8_t *graphData, int16_t minValue, int16_t maxValue, uint8_t maxValueIndex, uint8_t minValueIndex)
{
	int8_t correction = 0;
	
	//if((maxValue - minValue) / 2 > MaxGraphYIndex + 1)
	{
		if(minValueIndex > maxValueIndex)
			correction = 0 - minValue;
		else
			correction = (maxValue - MaxGraphYIndex * 2) * -1;
	}	

	for(int i = 0; i < MeasurementsCount; i++)
		graphData[i] = (roundData[i] + correction) / 2;
}
//---------------------------------------------------------------------------