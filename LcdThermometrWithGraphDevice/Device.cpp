/*
 * Device.cpp
 *
 * Created: 10.02.2015 17:41:32
 *  Author: Mihalych
 */ 
//---------------------------------------------------------------------------

#include "Device.h"
#include "DeviceConfiguration.h"
#include <stdio.h>
#include "BaseTypes/DateTime.h"
#include "Device/Ports.h"

//---------------------------------------------------------------------------


OWI_device Device::allDevices[MAX_DEVICES];

unsigned char Device::searchFlag = SEARCH_SENSORS;
unsigned char Device::crcFlag = 0;
unsigned char Device::sensorsCount = 0;

Lcd Device::lcd;

LcdController Device::lcdController(&Device::lcd);
TemperatureControl Device::topTempControl(&Device::lcdController, 0, 0);
TemperatureControl Device::bottomTempControl(&Device::lcdController, 0, 1);

//BaseLcdControl Device::topInfoControl(&Device::lcdController, 5, 0, 3, 1);
//BaseLcdControl Device::bottomInfoControl(&Device::lcdController, 5, 1, 3, 1);

//TimeControl Device::timeControl(&Device::lcdController, 0, 1);
SingleRowGraph Device::graph(&Device::lcdController, 5, 0, 3, 0);
SingleRowGraph Device::bottomGraph(&Device::lcdController, 5, 1, 3, 3);

TemperatureHolder Device::topTemperatureHolder(0, 3600000);
//TemperatureHolder Device::topTemperatureHolder(0, 5000);
TemperatureHolder Device::bottomTemperatureHolder(1, 3600000);

uint64_t Device::nextAllowClick = 0;
//---------------------------------------------------------------------------

void Device::Initialize(void)
{
	pinC1.SetAsOutput();
	pinC1.SetLowLevel();
	
	lcd.LCD_Init();		
	
	lcd.LCD_Clear();
	//lcd.LCD_SendString("Starting");
	//_delay_ms(2000);
	
	pinD0.SetAsOutput();
	pinD0.SetHightLevel();
	
	OWI_Init(BUS);
	
	//включается внешнее прерывание по падающему фронту
	pinD2.SetAsInputWithPullUp();		
	MCUCR = _BV(ISC01);
	GICR |= _BV(INT0);
	
	sei();
		
	DateTime::Initialize(260, 4);
	InitTimer2();
	
	lcd.LCD_Clear();
}
//---------------------------------------------------------------------------

void Device::InitTimer2(void)
{
	OCR2 = 60;
	//TCCR2 = _BV(WGM21) | _BV(CS22) | _BV(CS21);// | _BV(CS20);
	TCCR2 = _BV(WGM21) | _BV(CS22);// | _BV(CS21); | _BV(CS20);
	TIMSK |= _BV(OCIE2);  //Устанавливаем для него прерывание совпадения
}

//---------------------------------------------------------------------------
ISR(TIMER2_COMP_vect)
{
	DateTime::OnMillisecondsTick();
	DateTime::OnSecondsTick();		
}
//---------------------------------------------------------------------------

ISR(INT0_vect)
{
	if(DateTime::milliseconds > Device::nextAllowClick)
	{
		Device::nextAllowClick = DateTime::milliseconds + 200;
			
		pinC1.Reverse();		
	}
}
//---------------------------------------------------------------------------

void Device::MeasureAndSetScreen(void)
{	
#ifndef SIMULATION
	if (Device::searchFlag == SEARCH_SENSORS)
	{
		while(Device::sensorsCount == 0)
		{		    
			Device::sensorsCount = 0;
			Device::crcFlag = OWI_SearchDevices(Device::allDevices, MAX_DEVICES, BUS, &Device::sensorsCount);
		
			if (Device::crcFlag != SEARCH_CRC_ERROR)
			{
				Device::searchFlag = SENSORS_FOUND;				
			}
		}
	}
			
	if(sensorsCount > 0)
	{
		uint16_t temperature;
		
		Device::crcFlag = DS18B20_ReadTemperature(BUS, Device::allDevices[0].id, &temperature);
	
		if (Device::crcFlag == READ_CRC_ERROR)
		{
			Device::searchFlag = SEARCH_SENSORS;
		}

		Device::topTempControl.SetTemperature(temperature);
		ProceedTemperatureMeasurement(temperature, &Device::graph, &Device::topTemperatureHolder);
	}
	
	if(sensorsCount > 1)
	{
		uint16_t temperature;
			
		Device::crcFlag = DS18B20_ReadTemperature(BUS, Device::allDevices[1].id, &temperature);
			
		if (Device::crcFlag == READ_CRC_ERROR)
		{				
			Device::searchFlag = SEARCH_SENSORS;		
		}

		Device::bottomTempControl.SetTemperature(temperature);		
		ProceedTemperatureMeasurement(temperature, &Device::bottomGraph, &Device::bottomTemperatureHolder);
	}
#else
	Device::topTempControl.SetTemperature(-35);
	Device::bottomTempControl.SetTemperature(270);	
	//uint8_t wasUpdate = TemperatureHolder::ProceedMeasurement(270, 1);		
#endif
}
//---------------------------------------------------------------------------

void Device::RedrawLcd(void)
{
	topTempControl.CopyToLcdController();
	bottomTempControl.CopyToLcdController();
	//topInfoControl.CopyToLcdController();
	//bottomInfoControl.CopyToLcdController();
	//timeControl.CopyToLcdController();
	graph.CopyToLcdController();
	bottomGraph.CopyToLcdController();
	
	lcdController.Redraw(0);
}
//---------------------------------------------------------------------------

void Device::ProceedTemperatureMeasurement(uint16_t temperature, SingleRowGraph *graphControlPtr, TemperatureHolder *temperatureHolderPtr)
{
	uint8_t wasUpdate = temperatureHolderPtr->ProceedMeasurement(temperature);
		
	if(wasUpdate == 1)
	{
		int16_t restored[15] = {0};
		int8_t roundData[15] = {0};
		uint8_t grapgData[15] = {0};
			
		int16_t minValue = 0;
		int16_t maxValue = 0;
			
		uint8_t maxValueIndex;
		uint8_t minValueIndex;
			
		temperatureHolderPtr->ReadMeasurements(restored);
		temperatureHolderPtr->RoundMeasurements(restored, roundData, minValue, maxValue, maxValueIndex, minValueIndex);
		temperatureHolderPtr->CreateGraphData(roundData, grapgData, minValue, maxValue, maxValueIndex, minValueIndex);
		
		graphControlPtr->SetData(grapgData);
	}
}
//---------------------------------------------------------------------------