# MPLAB IDE generated this makefile for use with GNU make.
# Project: StopWatch.mcp
# Date: Wed Nov 03 22:28:59 2021

AS = MPASMWIN.exe
CC = mcc18.exe
LD = mplink.exe
AR = mplib.exe
RM = rm

StopWatch.cof : source.o
	$(LD) /p18F14K50 /l"C:\Program Files (x86)\Microchip\mplabc18\v3.47\lib" "source.o" /u_CRUNTIME /z__MPLAB_BUILD=1 /o"StopWatch.cof" /M"StopWatch.map" /W

source.o : source.c ../../../../../../../../Program\ Files\ (x86)/Microchip/mplabc18/v3.47/h/delays.h source.c ../../../../../../../../Program\ Files\ (x86)/Microchip/mplabc18/v3.47/h/p18f14k50.h
	$(CC) -p=18F14K50 "source.c" -fo="source.o" -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-

clean : 
	$(RM) "source.o" "StopWatch.cof" "StopWatch.hex"

