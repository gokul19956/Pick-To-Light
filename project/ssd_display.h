#ifndef SSD_DISPLAY_H  
#define SSD_DISPLAY_H  

#define MAX_SSD_CNT			4

#define HIGH				1
#define LOW					0

/*  
 *  SSD Segment interface to PORTD
 *
 *  RD7 RD6 RD5 RD4 RD3 RD2 RD1 RD0
 *   E   D   C   H   G   F   A   B
 *   1       1   0   1   0   0   0  
 */

/* This values are for common cathode display */
#define ZERO				0xE7
#define ONE					0x21
#define TWO					0xCB
#define THREE				0x6B
#define FOUR				0x2D
#define FIVE				0x6E
#define SIX					0xEE
#define SEVEN				0x23
#define EIGHT				0xEF
#define NINE				0x6F
#define DOT					0x10
#define BLANK				0x00
/* Need to fill All others */
#define MINUS				0x08

#define _U					0xE5
#define _S					0x6E
#define _t					0xCC
#define _N					0xA7
#define _i					0x80
#define _d					0xE9
#define _o					0xE8
#define _n					0xA8
#define _E					0xCE

extern unsigned char ssd[MAX_SSD_CNT];

void init_ssd_control(void);
void display(unsigned char data[]);

#endif
