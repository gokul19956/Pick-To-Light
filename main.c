#include "main.h"
#include "digital_keypad.h"
#include "ssd_display.h"
#include "timer0.h"
#include "i2c.h"
#include "at24c04.h"
#include "can.h"

const unsigned char digits[] = {ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE};
static unsigned char node_id[MAX_SSD_CNT];
static unsigned char can_tx_payload[13];
unsigned char ssd[MAX_SSD_CNT];

volatile bit message_received;

unsigned short convert_to_short(char data[])
{
	int i;
	unsigned short num = 0;
	for(i=0;i<4;i++)
	{
		num = data[i] + num * 10;
	}
	return num;/* convert the data[] array to short */;
}

void convert_to_byte(char data[], unsigned short value)
{
	int a,i = 3;  //node id is tranfered into array,that is tranferred  to UART
	do
	{
		a = value % 10 ;
		value = value / 10;
		data[i] = a; 
		/* Convert the short to array of bytes and store in data[] */
	} while (i--);
}

void construct_payload(unsigned short data, char sign)
{
	unsigned short temp;

	can_tx_payload[EIDH] = 0x00;
	can_tx_payload[EIDL] = 0x00;//EXTENDED IDENTIFIER REGISTER

	temp = convert_to_short(node_id); //SID-STANDARD IDENTIFIER REGISTER 
 
	temp = temp << 5; /* Explain Why?? *///sidh-->8 bit sidl--> remaining 3,,, for that we shift 5

	can_tx_payload[SIDH] = (temp >> 8) & 0xFF;
	can_tx_payload[SIDL] = (temp >> 0) & 0xFF;

	can_tx_payload[DLC] = 3;/* Fill the DLC count */ //DATA LENGTH COUNT-->ONLY 3 BYTES ARE USED

	can_tx_payload[D0] = sign; /* Append the sign *///RB0 D0 used for data and sign
	can_tx_payload[D1] = (data >> 0) & 0xFF; /* Append the LSB part of data */ // 
	can_tx_payload[D2] = (data >> 8) & 0xFF; /* Append the MSB part of data */
	can_tx_payload[D3] = 0;//DATA TO CAN (PAYLOAD)
	can_tx_payload[D4] = 0;
	can_tx_payload[D5] = 0;
	can_tx_payload[D6] = 0;
	can_tx_payload[D7] = 0; //total 8  segments we use only 3
}

void node_operation(unsigned char key)
{
	static unsigned short r_data;
	static unsigned short wait;
	unsigned short temp,rem;
	unsigned short i;

	if (can_receive())
	{
		/* Fill the received data in r_data variable */
		message_received = NOT_ACKED; 
		r_data = can_rx_payload[D1];
		r_data = (r_data << 8) | can_rx_payload[D0]; //
	}

	if (message_received == NOT_ACKED)
	{
		i = 3;//3.2.1.0
		temp = r_data; //received data
		do	
		{
            /* Write the logic to store r_data in ssd[] array */
			rem = temp % 10;
			ssd[i] = digits[rem];
			temp = temp / 10;
		} while (i--);

		if (!wait)
		{
			wait = DELAY_FACTOR;
		}
		else
		{
			if (key == ALL_RELEASED)
			{
				wait = DELAY_FACTOR;
			}
			key = ALL_RELEASED;
			wait--;
		}

		if (key == INC)
		{
            /* Increment r_data */

			if (r_data != 9999)
				r_data++;
		}

		if (key == CF)
		{
			/* Decrement r_data */

			if(r_data != 0)
				r_data--;
		}

		if (key == ACK) //if acknowledged
		{
			construct_payload(r_data, 'A');
			can_transmit(can_tx_payload);//transmit to can

			BUZZER = ON; //if acknowledged a buzzer is used to notify
			for (i = 5000; i--; );
			BUZZER = OFF;

			message_received = ACKED;
		}
	}
	else
	{
		ssd[0] = BLANK;
		ssd[1] = BLANK;
		ssd[2] = BLANK;
		ssd[3] = BLANK;
	}
}

unsigned short node_config(unsigned char key, unsigned short mode)
{
	static unsigned short screen;
	static bit sub_screen;
	static unsigned char cur_segment = 3,  j = 0;
	static unsigned char count[MAX_SSD_CNT];
	static unsigned short temp;
	unsigned short i;

	if (!sub_screen) /* Main Screen */
	{
		if (key == ACK)  //TO PRINT UST-update stock
		{
			if (screen++ > 0)
			{
				screen = 0;
			}
		}

		if (key == CF)
		{
			sub_screen = !sub_screen;
			cur_segment = 3;
		}

		if (screen == 0)
		{
			ssd[0] = _U;
			ssd[1] = MINUS;
			ssd[2] = _S;
			ssd[3] = _t;
		}
		else
		{
			ssd[0] = _n;
			ssd[1] = MINUS;
			ssd[2] = _i;
			ssd[3] = _d;
		}
	}
	else /* if (sub_screen) */
	{
		if (screen == 0)
		{
			ssd[0] = digits[count[0]];
			ssd[1] = digits[count[1]];
			ssd[2] = digits[count[2]];
			ssd[3] = digits[count[3]];

			if (key == INC)
			{
				if (count[cur_segment]++ > 8)
				{
					count[cur_segment] = 0;
				}
			}
		}
		else
		{
			ssd[0] = digits[node_id[0]];
			ssd[1] = digits[node_id[1]];
			ssd[2] = digits[node_id[2]];
			ssd[3] = digits[node_id[3]];

			if (key == INC)
			{
				if (node_id[cur_segment]++ > 8)
				{
					node_id[cur_segment] = 0;
				}
			}
		}

		ssd[cur_segment] |= DOT;

		if (key == CF)
		{
			/* Modify the feild position */
			ssd[cur_segment] &= 0xEF;
			if((cur_segment > 0) && (cur_segment <= 3))
            cur_segment--;
			j++;
			if(j==4)
			{
				cur_segment =3;
				j=0;
			}
		}
		if (key == ACK)
		{
			/* Take appropritate action based on screen */
			unsigned char byte;
			unsigned short value;
			if(screen == 0)
			{
				value=convert_to_short(count);
                construct_payload(value,'U');
				can_transmit(can_tx_payload);

				BUZZER = ON;
				for (i = 5000; i--; );
				BUZZER = OFF;

				for(i = 0; i < 4; i++ )
					count[i] = 0;

			}
			else
			{
				value = convert_to_short(node_id);
				byte = (value >> 8) & 0xFF;
				eeprom_at24c04_byte_write(0x01,byte);
				byte = (value << 0) & 0xFF;
				eeprom_at24c04_byte_write(0x00,byte);

				CAN_SET_OPERATION_MODE_NO_WAIT(e_can_op_mode_config);

				value = value << 5;  

				RXF0SIDH = (value >> 8) & 0xFF;
				RXF0SIDL = (value >> 0) & 0xFF;

				/* Enter CAN module into Normal mode */
				CAN_SET_OPERATION_MODE_NO_WAIT(e_can_op_mode_normal);
                screen=0;

			}
				message_received = ACKED;
	        	sub_screen = 0;
				mode = !mode;

		}
	}

	return mode;
}

unsigned short mode_selection(unsigned short mode)
{
	static bit once; //initialized to 0

	if (MODE_SWITCH && once) 
	{
		once = 0;
		mode = !mode; //flipped mode
	}
	else if (!MODE_SWITCH)
	{ 
		once = 1; //
	}

	return mode;
}

void pick_to_light(void)
{
	static unsigned short mode;
	unsigned char key;

	mode = mode_selection(mode);//initiazed to 0


	if (mode == e_config) //mode 1 since econfig=1
	{
	key = read_digital_keypad(STATE_CHANGE); //check for state change

		mode = node_config(key, mode); //
	}
	else /* if (mode == e_oper) */
	{
		key = read_digital_keypad(LEVEL_CHANGE);

		node_operation(key);
	}

	display(ssd);
}

void init_config(void)
{
    /* Call all the required inits */
    init_ssd_control();
	init_digital_keypad();
	init_can();
	init_i2c();
	/* Set Buzzer as output */
	TRISE0 = 0; 
	BUZZER = 0;

	/* Set Message Indicator LED as output */
	TRISB7 = 0;
	MSG_INDICATOR = 0;

	unsigned short temp = (eeprom_at24c04_random_read(NODE_ID_ADDR1) << 8) | eeprom_at24c04_random_read(NODE_ID_ADDR0); //address of node id is fetched

	if (temp > 127) //first data is tranferd to eeprom,eeprom contain both node id and num
	{
		temp = 10; //initial node id
	}

	convert_to_byte(node_id, temp);

	/* Enter CAN module into Configuration mode */
	CAN_SET_OPERATION_MODE_NO_WAIT(e_can_op_mode_config); //before Activation CAN ,can is set to initialization mode and then change to norml mode

	temp = temp << 5;  // 8bit registers..we have 11 bits we split into 8 n 3

	RXF0SIDH = (temp >> 8) & 0xFF;
	RXF0SIDL = (temp >> 0) & 0xFF;

	/* Enter CAN module into Normal mode */
	CAN_SET_OPERATION_MODE_NO_WAIT(e_can_op_mode_normal); 

	GIE = 1;
}

void main(void)
{    
	init_config();

	while (1)
	{
		pick_to_light();	//main function for calling repeatedly
	}
}
