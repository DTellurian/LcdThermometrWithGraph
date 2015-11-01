
#include "Lcd.h"
using namespace LcdNamespace;

//namespace LcdNamespace
	
//макросы для работы с битами
#define ClearBit(reg, bit)       reg &= (~(1<<(bit)))
#define SetBit(reg, bit)         reg |= (1<<(bit))	

#define FLAG_BF 7
//---------------------------------------------------------------------------

Lcd::Lcd(void)
{
	
}
//---------------------------------------------------------------------------

unsigned char __swap_nibbles(unsigned char data)
{
  asm volatile("swap %0" : "=r" (data) : "0" (data));
  return data;
}
//---------------------------------------------------------------------------

void Lcd::LCD_WriteComInit(unsigned char data)
{
  _delay_us(40);
  ClearBit(PORT_SIG, RS);	
#ifdef BUS_4BIT
  unsigned char tmp; 
  tmp  = PORT_DATA & 0x0f;
  tmp |= (data & 0xf0);
  PORT_DATA = tmp;		 
#else
  PORT_DATA = data;		
#endif  
  SetBit(PORT_SIG, EN);	        
  _delay_us(2);
  ClearBit(PORT_SIG, EN);	
}
//---------------------------------------------------------------------------

void LCD_CommonFunc(unsigned char data)
{
#ifdef BUS_4BIT  
  unsigned char tmp; 
  tmp  = PORT_DATA & 0x0f;
  tmp |= (data & 0xf0);

  PORT_DATA = tmp;		//вывод старшей тетрады 
  SetBit(PORT_SIG, EN);	        
  _delay_us(2);
  ClearBit(PORT_SIG, EN);	

  data = __swap_nibbles(data);
  tmp  = PORT_DATA & 0x0f;
  tmp |= (data & 0xf0);
 
  PORT_DATA = tmp;		//вывод младшей тетрады 
  SetBit(PORT_SIG, EN);	        
  _delay_us(2);
  ClearBit(PORT_SIG, EN);	 
#else 
  PORT_DATA = data;		    //вывод данных на шину индикатора 
  SetBit(PORT_SIG, EN);	     //установка E в 1
  _delay_us(2);
  ClearBit(PORT_SIG, EN);	//установка E в 0 - записывающий фронт
#endif
}
//---------------------------------------------------------------------------

void LCD_Wait(void)
{
#ifdef CHECK_FLAG_BF
  #ifdef BUS_4BIT
  
  unsigned char data;
  DDRX_DATA &= 0x0f;            //конфигурируем порт на вход
  PORT_DATA |= 0xf0;	        //включаем pull-up резисторы
  SetBit(PORT_SIG, RW);         //RW в 1 чтение из lcd
  ClearBit(PORT_SIG, RS);	//RS в 0 команды
  do{
    SetBit(PORT_SIG, EN);	
    _delay_us(2);
    data = PIN_DATA & 0xf0;      //чтение данных с порта
    ClearBit(PORT_SIG, EN);
    data = __swap_nibbles(data);
    SetBit(PORT_SIG, EN);	
    _delay_us(2);
    data |= PIN_DATA & 0xf0;      //чтение данных с порта
    ClearBit(PORT_SIG, EN);
    data = __swap_nibbles(data);
  }while((data & (1<<FLAG_BF))!= 0 );
  ClearBit(PORT_SIG, RW);
  DDRX_DATA |= 0xf0; 
  
  #else
  unsigned char data;
  DDRX_DATA = 0;                //конфигурируем порт на вход
  PORT_DATA = 0xff;	        //включаем pull-up резисторы
  SetBit(PORT_SIG, RW);         //RW в 1 чтение из lcd
  ClearBit(PORT_SIG, RS);	//RS в 0 команды
  do{
    SetBit(PORT_SIG, EN);	
    _delay_us(2);
    data = PIN_DATA;            //чтение данных с порта
    ClearBit(PORT_SIG, EN);	
  }while((data & (1<<FLAG_BF))!= 0 );
  ClearBit(PORT_SIG, RW);
  DDRX_DATA = 0xff; 
  #endif    
#else
  _delay_us(40);
#endif  
}
//---------------------------------------------------------------------------

//функция записи команды 
void Lcd::LCD_WriteCom(unsigned char data)
{
  LCD_Wait();
  ClearBit(PORT_SIG, RS);	//установка RS в 0 - команды
  LCD_CommonFunc(data);
}
//---------------------------------------------------------------------------

//функция записи данных
void Lcd::LCD_WriteData(unsigned char data)
{
  LCD_Wait();
  SetBit(PORT_SIG, RS);	    //установка RS в 1 - данные
  LCD_CommonFunc(data);
}
//---------------------------------------------------------------------------

//ooieoey eieoeaeecaoee
void Lcd::LCD_Init(void)
{
#ifdef BUS_4BIT
  DDRX_DATA |= 0xf0;
  PORT_DATA |= 0xf0; 
#else  
  DDRX_DATA |= 0xff;
  PORT_DATA |= 0xff;
#endif
  
  DDRX_SIG |= (1<<RW)|(1<<RS)|(1<<EN);
  PORT_SIG |= (1<<RW)|(1<<RS)|(1<<EN);
  ClearBit(PORT_SIG, RW);
  _delay_ms(40);
  
#ifdef HD44780  
  LCD_WriteComInit(0x30); 
  _delay_ms(10);
  LCD_WriteComInit(0x30);
  _delay_ms(1);
  LCD_WriteComInit(0x30);
#endif
  
#ifdef BUS_4BIT  
  //LCD_WriteComInit(0x20); //4 разрядная шина
  //LCD_WriteCom(0x20); //4-разрядная шина, 1 - строки
  
  LCD_WriteComInit(0x28); //4 разрядная шина
  LCD_WriteCom(0x28); //4-разрядная шина, 2 - строки    
#else
  LCD_WriteCom(0x38); //8-разрядная шина, 2 - строки
  //LCD_WriteCom(0x30); //8-разрядная шина, 2 - строки
#endif
  LCD_WriteCom(0x08);
  LCD_WriteCom(0x0c);  //дисплей вкл, курсор и мерцание выключены
  LCD_WriteCom(0x01);  //0b00000001 - очистка дисплея
  _delay_ms(2);
  LCD_WriteCom(0x06);  //0b00000110 - курсор движется вправо, сдвига нет
}
//---------------------------------------------------------------------------

//функция вывода строки из флэш памяти
void Lcd::LCD_SendStringFlash(char *str)
{
  unsigned char data = pgm_read_byte(str);
  while (data)
  {
    LCD_Wait();
    SetBit(PORT_SIG, RS);			
    LCD_CommonFunc(data);
    str++;
    data = pgm_read_byte(str);
  }
}
//---------------------------------------------------------------------------

//фунция вывода строки из RAM
void Lcd::LCD_SendString(char *str)
{
  unsigned char data;
  int counter = 0;
  SetBit(PORT_SIG, RS);			
  while (*str)
  {
	  /*
    //Добавил это для автоматического переноса
	if(counter == 8)
		LCD_WriteCom(0xc0);
	//До сюда	

	 
    //Добавил это для автоматического переноса
	if(counter == 32)
	LCD_WriteCom(0xc0);
	//До сюда
	*/
	  
	data = *str++;
    LCD_Wait();
    SetBit(PORT_SIG, RS);			
    LCD_CommonFunc(data);

	counter++;
  }
}
//---------------------------------------------------------------------------

void Lcd::LCD_Clear(void)
{
  LCD_WriteCom(0x01);
  _delay_ms(2);
}
//---------------------------------------------------------------------------