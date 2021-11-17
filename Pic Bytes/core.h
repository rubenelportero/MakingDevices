#ifndef __Core
#define __Core

rom const char init_screen[10] = {
	0x09,
	0x00,
	0x0A,
	0x0F,
	0x0B,
	0x07,
	0x0C,
	0x01,
	0x0F,
	0x00
};

char screenmap[32] = { 
     0b00000000,
     0b00000000,
     0b00000000,
     0b00000000,
     0b00000000,
     0b00000000,
     0b00000000,
     0b00000000,
     0b00000000,
     0b00000000,
     0b00000000,
     0b00000000,
     0b00000000,
     0b00000000,
     0b00000000,
     0b00000000,
     0b00000000,
     0b00000000,
     0b00000000,
     0b00000000,
     0b00000000,
     0b00000000,
     0b00000000,
     0b00000000,
     0b00000000,
     0b00000000,
     0b00000000,
     0b00000000,
     0b00000000,
     0b00000000,
     0b00000000,
     0b00000000
 };


char buttonmap[2] = { 
	0b00000000,		//Player one
	0b00000000		//Player two
};

/*
0b12345678
1: Up arrow
2: Down arrow
3: Left arrow
4: Rigth arrow
5: Encoder botton
6:
7: 
8:
*/

char game_ram[70]={ 
     0b00000000,
     0b00000000,
     0b00000000,
     0b00000000,
     0b00000000,     
	 0b00000000,
     0b00000000,
     0b00000000,
     0b00000000,
     0b00000000,
     0b00000000,
     0b00000000,
     0b00000000,
     0b00000000,
     0b00000000,     
	 0b00000000,
     0b00000000,
     0b00000000,
     0b00000000,
     0b00000000,
     0b00000000,
     0b00000000,
     0b00000000,
     0b00000000,
     0b00000000,     
	 0b00000000,
     0b00000000,
     0b00000000,
     0b00000000,
     0b00000000,
     0b00000000,
     0b00000000,
     0b00000000,
     0b00000000,
     0b00000000,     
	 0b00000000,
     0b00000000,
     0b00000000,
     0b00000000,
     0b00000000,
     0b00000000,
     0b00000000,
     0b00000000,
     0b00000000,
     0b00000000,     
	 0b00000000,
     0b00000000,
     0b00000000,
     0b00000000,
     0b00000000,
     0b00000000,
     0b00000000,
     0b00000000,
     0b00000000,
     0b00000000,     
	 0b00000000,
     0b00000000,
     0b00000000,
     0b00000000,
     0b00000000,
     0b00000000,
     0b00000000,
     0b00000000,
     0b00000000,
     0b00000000,     
	 0b00000000,
     0b00000000,
     0b00000000,
     0b00000000,
     0b00000000
 };

int snake_length=0;

void write_button(char buttonx, char nrplayer){
	char new_value= 0b10000000;
	nrplayer--;
	buttonx--;
	new_value = new_value >> buttonx;
	buttonmap[nrplayer] = buttonmap[nrplayer]|new_value;
}

char read_button(char buttonx, char nrplayer){
	char answer = 0b00000000;
	nrplayer--;
	answer = buttonmap[nrplayer] >> (8-buttonx);
	answer = answer&0b00000001;
	return answer;
}

void clean_button(void){
	buttonmap[0]=0;
	buttonmap[1]=0;
}

void screen_init(void) {
	char j,g;
	char shift_lata = 0b00000001;
	for(g=0;g<4;g++){
		for(j=0;j<10;j+=2){
			LATA=~shift_lata; // CS pin is pulled LOW
			WriteSPI(init_screen[j]); 
			WriteSPI(init_screen[j+1]); 
			LATA=0xFF;  // CS pin is pulled HIGH
		}

		shift_lata = shift_lata << 1; 
	}
}

void print_screen(void){
	char j,g;
	for(j=0;j<8;j++){
		char shift_lata = 0b00000001;
		char index=0;
		for(g=0;g<4;g++){
			LATA=~shift_lata; // CS pin is pulled LOW
			WriteSPI(j+1); // Select Display-Test register
			WriteSPI(screenmap[j+index]); // Disable Display-Test
			LATA=0xFF;  // CS pin is pulled HIGH
			shift_lata = shift_lata << 1;
			index += 8;
		}
	}
}

char read_screen(char x, char y){
	char answer = 0b00000000;
	char index = 0;
	x--;
	y--;
	if(x==8 || x == 9){
		if(y>=8 && y<16){
			y-=8;
		}
		if(y>=16){
			y-=16;
		}
		x -=8;
		index = 24;
	}
	x = 7 - x;
	answer = screenmap[y+index] >> x;
	answer = answer&0b00000001;
	return answer;
}

void write_screen(char x, char y, char value){
	char new_value= 0b10000000;
	char index = 0;
	x--;
	y--;
	if(x==8 || x == 9){
		if(y>=8 && y<16){
			new_value= 0b00100000;
			y-=8;
		}
		if(y>=16){
			new_value= 0b00001000;
			y-=16;
		}
		x -=8;
		index = 24;
	}
	value = value&0b00000001;
	new_value = new_value >> x;
	if(value==1){
		screenmap[y+index] = screenmap[y+index]|new_value;
	} else {
		screenmap[y+index] = screenmap[y+index]&~new_value;
	}
}

void button_start(void){
	TRISD = 0;
	LATD = 0x00;
	TRISB=0b11111101;
	INTCON2bits.RBPU = 0;
}

// ---------------- BUTTON ---------------------------- //
void check_movement(void){
	if(read_button(4,1)==1){ //rigth
		game_ram[65] = 0b00000000;
	}
	if(read_button(3,1)==1){ //left
		game_ram[65] = 0b00000001;
	}
	if(read_button(2,1)==1){ //down
		game_ram[65] = 0b00000011;
	}
	if(read_button(1,1)==1){ //up
		game_ram[65] = 0b00000010;
	}
}
void check_buttons(void){
	char i,index,player;
	if((PORTB&0b11100000)!=0b11100000){
   	for (i=0b00000001;(i<0b00010000);i=i<<1)  //Bucle for que rota un bit entre el nibble alto del puerto B y para cuando se detecta un boton pulsado
	{
		LATD=~i;
  		if(i<0b00000100){
			player = 1;
		} else {
			player = 2;
		}
		if(i==0b00000010||i==0b00001000){
			index = 2;
		} else {
			index = 0;
		}
		if((PORTB&0b00100000)==0b00000000){
			write_button(1+index,player);
		}
		if((PORTB&0b01000000)==0b00000000){
 			write_button(2+index,player);
		}
		if((PORTB&0b10000000)==0b0000000){
			write_button(5,player);
		}
	}
	LATD=0X00;
	}
}

#endif