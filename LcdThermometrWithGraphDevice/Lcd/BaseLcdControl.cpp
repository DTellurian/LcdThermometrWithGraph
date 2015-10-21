/*
 * BaseLcdControl.cpp
 *
 * Created: 13.02.2015 17:08:38
 *  Author: Mihalych
 */ 
//---------------------------------------------------------------------------

#include "BaseLcdControl.h"
#include <stdlib.h>
#include <string.h>
//---------------------------------------------------------------------------

BaseLcdControl::BaseLcdControl(LcdController* lcdControllerPtr, uint8_t x, uint8_t y, uint8_t width, uint8_t height)
{
	this->lcdControllerPtr = lcdControllerPtr;
	
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	
	controllBufferToWrite = (char**)calloc(height, sizeof(char*));
	
	for(uint8_t y = 0; y < height; y++)
		controllBufferToWrite[y] = (char*)calloc(width + 1, sizeof(char));		
}
//---------------------------------------------------------------------------

char* BaseLcdControl::GetBufferPointerToWrite(uint8_t innerControlRowIndex)
{
	return controllBufferToWrite[innerControlRowIndex];	
}
//---------------------------------------------------------------------------

void BaseLcdControl::Clear(void)
{
	for(uint8_t yPos = 0; yPos < height; yPos++)
	{
		char* buffer = GetBufferPointerToWrite(yPos);
		
		for(uint8_t xPos = 0; xPos < width; xPos++)
			buffer[xPos] = 0x20;
	}
}
//---------------------------------------------------------------------------

void BaseLcdControl::CopyToLcdController(void)
{
	for(uint8_t yPos = 0; yPos < height; yPos++)
		memcpy(lcdControllerPtr->bufferedtState[y + yPos] + x, controllBufferToWrite[yPos], width);
}
//---------------------------------------------------------------------------

Lcd* BaseLcdControl::GetLcdPtr(void)
{
	return lcdControllerPtr->lcdPtr;
}
//---------------------------------------------------------------------------