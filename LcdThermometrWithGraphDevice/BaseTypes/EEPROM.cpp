/*
 * EEPROM.cpp
 *
 * Created: 05.08.2012 23:56:01
 *  Author: Dmitriy
 */ 
//---------------------------------------------------------------------------

#include "EEPROM.h"
#include <avr/io.h>
//---------------------------------------------------------------------------

void EEPROM::Write(unsigned int address, unsigned char data)
{	
	/* Wait for completion of previous write */
	while(EECR & (1<<EEWE))
	;
	/* Set up address and data registers */
	EEAR = address;
	EEDR = data;
	/* Write logical one to EEMWE */
	EECR |= (1<<EEMWE);
	/* Start eeprom write by setting EEWE */
	EECR |= (1<<EEWE);
}

unsigned char EEPROM::Read(unsigned int addresss)
{
	/* Wait for completion of previous write */
	while(EECR & (1<<EEWE))
	;
	/* Set up address register */
	EEAR = addresss;
	/* Start eeprom read by writing EERE */
	EECR |= (1<<EERE);
	/* Return data from data register */
	return EEDR;		
}
//---------------------------------------------------------------------------

void EEPROM::ShiftLeft(uint8_t startAddresss, uint8_t bufferLength)
{
	for(uint8_t i = 1; i < bufferLength; i++)
	{
		uint8_t data = Read(startAddresss + i);
		Write(startAddresss + i - 1, data);
	}
}
//---------------------------------------------------------------------------