/*
 * EEPROM.h
 *
 * Created: 05.08.2012 23:53:37
 *  Author: Dmitriy
 */ 
//---------------------------------------------------------------------------

#ifndef EEPROM_H_
#define EEPROM_H_
//---------------------------------------------------------------------------

#include <inttypes.h>
//---------------------------------------------------------------------------

class EEPROM
{
	public:
		static void Write(unsigned int address, unsigned char data);
		static unsigned char Read(unsigned int addresss);
		static void ShiftLeft(uint8_t startAddresss, uint8_t bufferLength);
	protected:
	private:
		EEPROM(void);
};
//---------------------------------------------------------------------------
#endif /* EEPROM_H_ */