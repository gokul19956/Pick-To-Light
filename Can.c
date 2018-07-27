#include "pic_specific.h"
#include "can.h"
#include "main.h"

/* Global Variables */
unsigned char can_rx_payload[13];

/* Configure the CAN Module */
void init_can(void)
{
	/* CAN_TX = RB2, CAN_RX = RB3 */
	TRISB2 = 0;								/* CAN TX */
	TRISB3 = 1;								/* CAN RX */

	/* Enter CAN module into config mode */
	CANSTAT &= 0x1F;						/* clear previous mode */
	CANSTAT |= 0x80;                       	/* set new mode */

	/* Wait untill desired mode is set */
	while (CANSTAT != 0x80);

	/* Enter CAN module into Mode 0 */
	ECANCON = 0x00;

	/* Initialize CAN Timing 8MHz */
	BRGCON1 = 0xE1;							/* 1110 0001, SJW=4, TQ, BRP 4 */
	BRGCON2 = 0x1B;							/* 0001 1011, SEG2PHTS 1 sampled once PS1=4TQ PropagationT 4TQ */
	BRGCON3 = 0x03;							/* 0000 0011, PS2, 4TQ */

	/*
	 * Enable Filters
	 * Filter 0
	 */
	RXFCON0 = 0x01;     

    /* Receive Acceptance Filter Mask */
	/* Set the Filter Mask range such a way that we receive data for this node */
	RXM0EIDH = 0xFF;    /* 0's for EID and SID */
	RXM0EIDL = 0xFF;
	RXM0SIDH = 0xFF;
	RXM0SIDL = 0xFF;

	/* Node ID is set in application */

	/* Enter CAN module into Loop back mode */
	CAN_SET_OPERATION_MODE_NO_WAIT(e_can_op_mode_normal); 

	/* Set Receive Mode for buffers */
	RXB0CON = 0x00;
}

/* Check the buffers, if it have message */
unsigned char can_receive(void)
{
	if (RXB0FUL) /* CheckRXB0 */
	{
		can_rx_payload[EIDH] = RXB0EIDH; 
		can_rx_payload[EIDL] = RXB0EIDL;
		can_rx_payload[SIDH] = RXB0SIDH;
		can_rx_payload[SIDL] = RXB0SIDL;
		can_rx_payload[DLC] = RXB0DLC;
		can_rx_payload[D0] = RXB0D0;
		can_rx_payload[D1] = RXB0D1;
		can_rx_payload[D2] = RXB0D2;
		can_rx_payload[D3] = RXB0D3;
		can_rx_payload[D4] = RXB0D4;
		can_rx_payload[D5] = RXB0D5;
		can_rx_payload[D6] = RXB0D6;
		can_rx_payload[D7] = RXB0D7;

		RXB0FUL = 0;

		return TRUE;
	}
	else
	{
		return FALSE;
	}    
}

/* Transmit Sample Mesaage */
void can_transmit(const unsigned char *can_tx_payload)
{
	TXB0EIDH = can_tx_payload[EIDH];   	/* Extended Identifier */
	TXB0EIDL = can_tx_payload[EIDL];   	/* Extended Identifier */
	TXB0SIDH = can_tx_payload[SIDH];   	/* Standard Identifier */
	TXB0SIDL = can_tx_payload[SIDL];   	/* Standard Identifier */
	TXB0DLC = can_tx_payload[DLC];    	/* can_tx_payload Length Count */
	TXB0D0 = can_tx_payload[D0];		/* can_tx_payloadByte 0 */
	TXB0D1 = can_tx_payload[D1];		/* can_tx_payloadByte 1 */
	TXB0D2 = can_tx_payload[D2];		/* can_tx_payloadByte 2 */
	TXB0D3 = can_tx_payload[D3];		/* can_tx_payloadByte 3 */
	TXB0D4 = can_tx_payload[D4];		/* can_tx_payloadByte 4 */
	TXB0D5 = can_tx_payload[D5];		/* can_tx_payloadByte 5 */
	TXB0D6 = can_tx_payload[D6];		/* can_tx_payloadByte 6 */
	TXB0D7 = can_tx_payload[D7];		/* can_tx_payloadByte 7 */

	TXB0REQ = 1;						/* Set the buffer to transmit */
}
