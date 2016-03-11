/*
 * SingleRowGraph.cpp
 *
 * Created: 04.03.2015 11:31:10
 *  Author: Mihalych
 * 11.03.2016 Shorstok
 * Added option to draw more readable solid bar graph
 */ 
//---------------------------------------------------------------------------

#include "SingleRowGraph.h"
#include <stdlib.h>
#include <stdio.h>
//---------------------------------------------------------------------------

SingleRowGraph::SingleRowGraph(LcdController* lcdControllerPtr, uint8_t x, uint8_t y, uint8_t width, uint8_t userSymbolStartIndex)
	:BaseLcdControl(lcdControllerPtr, x, y, width, 1),
	bDrawSolidGraph(false)	//default: draw classic dotted graph. Set to 'true' to draw fancy solid bars
{
	createdSymbolsValue = (uint8_t*)calloc(width * 5, sizeof(uint8_t));
	this->userSymbolStartIndex = userSymbolStartIndex;
}
//---------------------------------------------------------------------------

#include "../Device.h"

	//char batteryArray[8]={
	//0b0001110,
	//0b0010001,
	//0b0010001,
	//0b0011111,
	//0b0011111,
	//0b0011111,
	//0b0011111,
	//0b0000000};

void SingleRowGraph::SetData(uint8_t* data)
{	
	char* buffer = GetBufferPointerToWrite();
		
	for(uint8_t symbolCounter = 0; symbolCounter< width; symbolCounter++)
	{					
		char symbolData[8] = {0};
		uint8_t needToSendSymbol = 0;
		
		for(uint8_t rowCounter = 0; rowCounter < 8; rowCounter++)
		{
			for(uint8_t columnCounter = 0; columnCounter < 5; columnCounter++)
			{
				uint8_t currentDataIndex = symbolCounter * 5 + columnCounter;
				
				if(data[currentDataIndex] != createdSymbolsValue[currentDataIndex])
				{
					needToSendSymbol = 1;
					createdSymbolsValue[currentDataIndex] = data[currentDataIndex];
				}
				
				//Fill all pixels below temperature line
				if(bDrawSolidGraph && 7 - data[currentDataIndex] <= rowCounter)
					symbolData[rowCounter] |= 1 << (5 - 1 - columnCounter);	
				else if(7 - data[currentDataIndex] == rowCounter)//Для проверки прорисовки нижней строки
				//if(6 - data[currentDataIndex] == rowCounter)
					symbolData[rowCounter] |= 1 << (5 - 1 - columnCounter);						
			}
		}
		
		if(needToSendSymbol)
		{
			char writeCommand = 0x40 | (8 * (symbolCounter + userSymbolStartIndex));//0b1000000;
					
			GetLcdPtr()->LCD_WriteCom(writeCommand);
					
			for(uint8_t rowCount = 0; rowCount < 8; rowCount++)
				GetLcdPtr()->LCD_WriteData(symbolData[rowCount]);			
		}
		
		buffer[symbolCounter] = 0x08 + userSymbolStartIndex + symbolCounter;//0x08 - потому что в LcdController есть проверка на 0, и если ноль выводится пробел
	}	
}
//---------------------------------------------------------------------------