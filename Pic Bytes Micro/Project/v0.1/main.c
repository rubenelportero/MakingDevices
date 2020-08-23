/*	Making New Bytes 2020
	Rubén García Segovia
	  Pic Bytes Micro
*/
#include <p18f4550.h>
#include <delays.h>
#include "core.h"
#include "snake.h"

// CONFIG1H
#pragma config FOSC = HS // Oscillator Selection bits (HS oscillator, PLL enabled (HSPLL))
#pragma config FCMEN = OFF // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor disabled)
#pragma config IESO = OFF // Internal/External Oscillator Switchover bit (Oscillator Switchover mode disabled)
#pragma config LVP = OFF //Disable low voltage programmer so we can use RB5.

/*
Screen: 10x16
*/

void _low_isr (void);
void _high_isr (void);

#pragma code low_vector=0x18 //Low interrupt priority starts at 0x18
void low_interrupt(void)
{
_asm goto _low_isr _endasm
}

#pragma code high_vector=0x08 //High interrupt priority starts at 0x08
void high_interrupt(void)
{
_asm goto _high_isr _endasm
}
#pragma code


#pragma interrupt _low_isr
char state = 0;
char game=0;
void _low_isr (void)
{
if(INTCONbits.TMR0IF) //Timer0 interrupt
{

	clean_buttons();
	update_buttons();
	print_screen();
	if(state==1&&game==1){
		check_movement();
	}
	TMR0H = 0xFE;
	TMR0L = 0x70;
	INTCONbits.TMR0IF = 0; // reset overflow bit
}
}

#pragma interrupt _high_isr
void _high_isr (void)
{
if(INTCONbits.INT0IF) //Reset 
{
	INTCONbits.INT0IF = 0;
}
}

/* ****************** MAIN ****************** */

void main(void)
{
	splash_init();
	menu();
	//snake_init();
	while(1){
		Delay10KTCYx(50);
		if(state==1&&game==1){
			move_snake();
		}
	}
}




