/*
 * LcdDefines.h
 *
 * Created: 10.02.2015 15:00:41
 *  Author: Mihalych
 */ 


#ifndef LCDDEFINES_H_
#define LCDDEFINES_H_
//---------------------------------------------------------------------------

//���� � �������� ���������� ���� ������ ���
#define PORT_DATA PORTD
#define PIN_DATA  PIND
#define DDRX_DATA DDRD

//���� � �������� ���������� ����������� ������ ���
#define PORT_SIG PORTB
#define PIN_SIG  PINB
#define DDRX_SIG DDRB

//������ ������� � ������� ���������� ����������� ������ ���
#define RS 3
#define RW 6
#define EN 7

//#define CHECK_FLAG_BF
#define BUS_4BIT
//#define HD44780
//******************************************************************************

//---------------------------------------------------------------------------
#endif /* LCDDEFINES_H_ */