#ifndef __SPI
#define __SPI

void SPI_Init_Master(void)
{
    /* PORT definition for SPI pins*/    
	TRISA=0;
    TRISBbits.TRISB1=0;		/* RB1 as output(SCK) */
    TRISCbits.TRISC7=0;		/* RC7 as output(SDO) */

    /* To initialize SPI Communication configure following Register*/
    SSPSTAT=0x40;		/* Data change on rising edge of clk , BF=0*/
    SSPCON1=0x22;		/* Master mode,Serial enable,
				idle state low for clk, fosc/64 */ 
    PIR1bits.SSPIF=0;

    /* Disable the ADC channel which are on for multiplexed pin when
    used as an input */    
    ADCON0=0;			/* This is for de-multiplexed the 
				SCL and SDI from analog pins*/
    ADCON1=0x0F;		/* This makes all pins as digital I/O */
}

void Write_SPI(unsigned char x)
{
    unsigned char data_flush;
    SSPBUF=x;			// Copy data in SSBUF to transmit 
    while(!PIR1bits.SSPIF);	// Wait for complete 1 byte transmission 
    PIR1bits.SSPIF=0;		// Clear SSPIF flag 
    data_flush=SSPBUF;		// Flush the data 
}

#endif