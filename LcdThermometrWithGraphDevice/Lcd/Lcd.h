/*
 * Lcd.h
 *
 * Created: 10.12.2011 23:58:30
 *  Author: Dmitriy
 */ 

#ifndef LCD_H_
#define LCD_H_

namespace LcdNamespace
{
	
#include <avr/io.h>
#include <math.h>
#include <util/delay.h>
#include <avr/pgmspace.h>
#include "LcdDefines.h"
//---------------------------------------------------------------------------

//макросы
/*позиционирование курсора*/
#define LCD_Goto(x,y) LCD_WriteCom(((((y)& 1)*0x40)+((x)& 15))|128) 
//---------------------------------------------------------------------------

class Lcd
{
	public:
		Lcd(void);
		void LCD_Init(void);//инициализация портов и жкд
		void LCD_Clear(void);//очистка дисплея
		void LCD_WriteData(unsigned char data); //выводит байт данных на жкд
		void LCD_WriteCom(unsigned char data); //посылает команду жкд
		void LCD_SendStringFlash(char *str); 
		void LCD_SendString(char *str);
	protected:
	private:
		Lcd(const Lcd&);
		void LCD_WriteComInit(unsigned char data);
	};
		
}
//---------------------------------------------------------------------------
#endif /* LCD_H_ */