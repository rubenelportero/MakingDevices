# MPLAB IDE generated this makefile for use with GNU make.
# Project: PicBytes.mcp
# Date: Wed Jun 10 20:30:35 2020

AS = MPASMWIN.exe
CC = mcc18.exe
LD = mplink.exe
AR = mplib.exe
RM = rm

PicBytes.cof : main.o
	$(LD) /p18F4550 /l"C:\Program Files (x86)\Microchip\mplabc18\v3.47\lib" "main.o" /u_CRUNTIME /u_DEBUG /z__MPLAB_BUILD=1 /z__MPLAB_DEBUG=1 /o"PicBytes.cof" /M"PicBytes.map" /W

main.o : main.c ../../../../../Program\ Files\ (x86)/Microchip/mplabc18/v3.47/h/delays.h core.h spi.h snake.h main.c config.h ../../../../../Program\ Files\ (x86)/Microchip/mplabc18/v3.47/h/p18f4550.h
	$(CC) -p=18F4550 "main.c" -fo="main.o" -D__DEBUG -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-

clean : 
	$(RM) "main.o" "PicBytes.cof" "PicBytes.hex"

