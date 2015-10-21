/*
 * Device.h
 *
 * Created: 10.02.2015 17:41:22
 *  Author: Mihalych
 */ 


#ifndef DEVICE_H_
#define DEVICE_H_
//---------------------------------------------------------------------------

#include "DS18B20Support/DS18B20.h"
#include "DS18B20Support/DS18B20Defines.h"
#include "Lcd/Lcd.h"
#include "Lcd/LcdController.h"
#include "Lcd/TemperatureControl.h"
#include "Lcd/TimeControl.h"
#include "Lcd/SingleRowGraph.h"
#include "TemperatureHolder.h"
//---------------------------------------------------------------------------

//#define SIMULATION

using namespace LcdNamespace;

class Device
{
	public:
	static void Initialize(void);
	
	
	static OWI_device allDevices[MAX_DEVICES];

	static unsigned char searchFlag;
	static unsigned char crcFlag;
	static unsigned char sensorsCount;	
		
	static LcdController lcdController;	
	
	static TemperatureControl topTempControl;
	static TemperatureControl bottomTempControl;
	
	//static BaseLcdControl topInfoControl;
	//static BaseLcdControl bottomInfoControl;
	
	//static TimeControl timeControl;
	static SingleRowGraph graph;
	static SingleRowGraph bottomGraph;
	
	static TemperatureHolder topTemperatureHolder;
	static TemperatureHolder bottomTemperatureHolder;
	
	static void MeasureAndSetScreen(void);
	
	static Lcd lcd;
	
	static void RedrawLcd(void);
	static uint64_t nextAllowClick;
	
	private:	
	
		Device(void);
		Device(Device&);
		
		static void InitTimer2(void);
		
		static void ProceedTemperatureMeasurement(uint16_t temperature, SingleRowGraph *graphControlPtr, TemperatureHolder *temperatureHolderPtr);
		
};
//---------------------------------------------------------------------------

#endif /* DEVICE_H_ */