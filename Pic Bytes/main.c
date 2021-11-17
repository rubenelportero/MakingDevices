/*	Making New Bytes 2020
	Rubén García Segovia
*/
#include "config.h"
#include <p18f4550.h>
#include <delays.h>
#include <stdlib.h> 
#include "core.h"
#include "spi.h"
#include "snake.h"

/*
Screen: 10x24
Functions: 
	void screen_init(void);

	void write_screen(int x,int y, char value);
		where value either 1 or 0

	char read_screen(int x,int y);

	void print_screen(void);
	
*/
void timer0_start(void);

void _low_isr (void);
void _high_isr (void);

#pragma code low_vector=0x18 //Low interrupt priority starts at 0x08
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
void _low_isr (void)
{
if(INTCONbits.TMR0IF) //Timer0 interrupt
{
	clean_button();
	print_screen();
	check_buttons();
	check_movement();
	INTCONbits.TMR0IF = 0; // reset overflow bit
}
if(INTCONbits.RBIF) //Any button pressed
{
	INTCONbits.RBIF = 0; // reset overflow bit
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
	SPI_Init_Master();	
	Delay10KTCYx(25);
	screen_init();
	timer0_start();
	button_start();
	snake_init();
	while(1){
		Delay10KTCYx(150);
		move_snake();
	}
}

void timer0_start(void){
    T0CONbits.T08BIT = 0;   // 16-bit timer
    T0CONbits.T0CS = 0;     // increment on instruction cycle input
    T0CONbits.T0SE = 0;     // increment on low--> high transition of clock
    T0CONbits.PSA = 0;
	PIE2bits.USBIE = 0;
	T0CONbits.T0PS2 = 0;
	T0CONbits.T0PS1 = 0;
	T0CONbits.T0PS0 = 0;
	TMR0H = 0x15;
	TMR0L = 0xA0;
    RCONbits.IPEN       = 1;    //Enable Interrupt Priorities
    INTCONbits.GIEL     = 1;    //Enable Low Priority Interrupt
    INTCONbits.GIEH     = 1;    // disable high priority interrupts        
    INTCONbits.TMR0IE   = 1;    //Enable Timer0 Interrupt
    INTCON2bits.TMR0IP  = 0;    //TMR0 set to low Priority Interrupt
    INTCONbits.TMR0IF = 0;  // T0 int flag bit cleared before starting
    T0CONbits.TMR0ON = 1;   // timer0 START
}

