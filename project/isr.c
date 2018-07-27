#include "pic_specific.h"
#include "main.h"
#include "ssd_display.h"

void interrupt isr(void)
{
	static unsigned short count1;

	if (TMR0IF)
	{
		TMR0 = TMR0 + 8;

		if (message_received == NOT_ACKED)
		{
			if (count1++ == 10000)
			{
				count1 = 0;

				MSG_INDICATOR = !MSG_INDICATOR;
			}
		}
		else
		{
			count1 = 0;
			MSG_INDICATOR = OFF;
		}

		TMR0IF = 0;
	}
}
