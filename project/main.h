#ifndef MAIN_H
#define MAIN_H

#include "pic_specific.h"

#define _XTAL_FREQ 20000000

/* Defines the data */
#define TRUE				1
#define FALSE				0

#define ON					1
#define OFF					0

#define	ACKED				0
#define	NOT_ACKED			1

#define DELAY_FACTOR		5

/* EEPROM offsets */
#define NODE_ID_ADDR0		0x00
#define NODE_ID_ADDR1		0x01

typedef enum Modes
{
	e_oper,
	e_config
};

#define INC					SWITCH1
#define CF					SWITCH2
#define ACK					SWITCH3

extern volatile bit message_received;
extern volatile unsigned char cur_segment;
extern bit sub_screen;

#endif
