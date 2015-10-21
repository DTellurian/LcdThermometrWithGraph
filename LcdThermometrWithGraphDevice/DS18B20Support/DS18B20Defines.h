
/*
 * DS18B20Defines.h
 *
 * Created: 10.02.2015 14:54:10
 *  Author: Mihalych
 */ 

#ifndef DS18B20DEFINES_H_
#define DS18B20DEFINES_H_
//---------------------------------------------------------------------------

//�����, � �������� ���������� 1Wire ����������
#define BUS   OWI_PIN_0

//���������� ��������� �� ���� 1Wire
#define MAX_DEVICES       0x02

#define     CPU_FREQUENCY   1.000

// Port configuration registers for 1-Wire buses.
// Make sure that all three registers belong to the same port.
#define     OWI_PORT        PORTD   //!< 1-Wire PORT Data register.
#define     OWI_PIN         PIND    //!< 1-Wire Input pin register.
#define     OWI_DDR         DDRD    //!< 1-Wire Data direction register.
//---------------------------------------------------------------------------
#endif /* DS18B20DEFINES_H_ */