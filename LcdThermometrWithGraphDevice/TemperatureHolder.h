/*
 * TemperatureHolder.h
 *
 * Created: 05.03.2015 12:41:38
 *  Author: Mihalych
 */ 

#ifndef TEMPERATUREHOLDER_H_
#define TEMPERATUREHOLDER_H_
//---------------------------------------------------------------------------

#include <inttypes.h>
//---------------------------------------------------------------------------

class TemperatureHolder
{
	public:
		TemperatureHolder(uint8_t sensorIndex, uint64_t measurementPeriod);			
	
		uint8_t ProceedMeasurement(int16_t temperature);//Returns flag? that indicates that new value was written in EEPROM
	
		void ReadMeasurements(int16_t *bufferPtr);
		void RoundMeasurements(int16_t *deviceValue, int8_t *roundData, int16_t &minValue, int16_t &maxValue, uint8_t &maxValueIndex, uint8_t &minValueIndex);
		void CreateGraphData(int8_t *roundData, uint8_t *graphData, int16_t minValue, int16_t maxValue, uint8_t maxValueIndex, uint8_t minValueIndex);
	private:
		TemperatureHolder(void);
	
		uint8_t sensorIndex;
		
		int32_t measurementsSumm;
		uint16_t measurementsCounter;
		
		uint64_t measurementPeriod;
		uint64_t nextMeasurementTime;
		
		void WriteNextHoursValue(int16_t hourValue, uint8_t sensorIndex);		
};
//---------------------------------------------------------------------------
#endif /* TEMPERATUREHOLDER_H_ */