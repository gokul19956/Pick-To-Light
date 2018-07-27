#ifndef PIC_SPECIFIC_H
#define PIC_SPECIFIC_H

#include <xc.h>

#define _XTAL_FREQ 20000000

#pragma config OSC			= XT
#pragma config WDT			= OFF
#pragma config BOREN		= OFF
#pragma config PBADEN		= OFF
#pragma config LVP			= OFF

#define CLCD_PORT			PORTD
#define CLCD_EN				RC2
#define CLCD_RS				RC1
#define CLCD_RW				RC0
#define CLCD_BUSY			RD7
#define PORT_DIR			TRISD7

#define RB0					PORTBbits.RB0
#define RB1					PORTBbits.RB1
#define RB2					PORTBbits.RB2
#define RB3					PORTBbits.RB3
#define RB4					PORTBbits.RB4
#define RB5					PORTBbits.RB5
#define RB6					PORTBbits.RB6
#define RB7					PORTBbits.RB7

#define RC0					PORTCbits.RC0
#define RC1					PORTCbits.RC1
#define RC2					PORTCbits.RC2
#define RC3					PORTCbits.RC3
#define RC4					PORTCbits.RC4
#define RC5					PORTCbits.RC5
#define RC6					PORTCbits.RC6
#define RC7					PORTCbits.RC7

#define RE0					PORTEbits.RE0
#define RE1					PORTEbits.RE1
#define RE2					PORTEbits.RE2
#define RE3					PORTEbits.RE3
#define RE4					PORTEbits.RE4
#define RE5					PORTEbits.RE5
#define RE6					PORTEbits.RE6
#define RE7					PORTEbits.RE7

#define KEY_PORT			PORTC

#define MODE_SWITCH			RB0

#define BUZZER				RE0

#define SSD_DATA_PORT		PORTD
#define SSD_CNT_PORT		PORTA

#define MSG_INDICATOR		RB7

#endif
