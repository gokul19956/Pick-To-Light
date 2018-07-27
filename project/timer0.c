#include "main.h"
#include "timer0.h"

void init_timer0(void)
{
	/*
	 * Setting instruction cycle clock (Fosc / 4) as the source of
	 * timer0
	 */
	T0CS = 0;

	TMR0 = 6;

	/* Clearing timer0 overflow interrupt flag bit */
	T0IF = 0;

	/* Enabling timer0 overflow interrupt */
	TMR0IE = 1;
}
