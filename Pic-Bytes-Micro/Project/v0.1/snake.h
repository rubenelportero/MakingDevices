#ifndef __snake_game
#define __snake_game

// ----------------- SNAKE GAME ----------------------- //
void snake_init(void){
	int j;
	game_ram[60]=7;	//head x axis
	game_ram[61]=3;	//head y axis
	game_ram[62]=4;	//tale x axis
	game_ram[63]=3; //tale y axis
	game_ram[66]=0; // tale pointer index
	game_ram[64]=0; // tale pointer position
	snake_length=4;	// length of the snake
	for(j=4;j<8;j++){
		write_screen(j,3,1);
	}
}

void food(void){
	if(game_ram[68]==0){
		
	}
}

void move_snake(void){
	int head_index_pointer,head_position_pointer;
	head_position_pointer = snake_length + game_ram[64] - 1;
	head_index_pointer = game_ram[66];
	if(head_position_pointer>3){
		head_index_pointer = game_ram[66] + head_position_pointer/4;
		head_position_pointer = head_position_pointer % 4;
	}
	if(game_ram[65]==0b00000000){ //rigth
		game_ram[60]++;
	}
	if(game_ram[65]==0b00000011){//down
		game_ram[61]++;
	}
	if(game_ram[65]==0b00000010){ //up
		game_ram[61]--;
	}
	if(game_ram[65]==0b00000001){ //left
		game_ram[60]--;
	}
	write_screen(game_ram[62],game_ram[63],0);
	write_screen(game_ram[60],game_ram[61],1);
	game_ram[head_index_pointer] = game_ram[head_index_pointer]&~(0b00000011<<(6-(2*head_position_pointer)));
	game_ram[head_index_pointer] = game_ram[head_index_pointer]|(game_ram[65]<<(6-(2*head_position_pointer)));
	if(((game_ram[game_ram[66]]<<(game_ram[64]*2))&0b11000000)==0b00000000){
		game_ram[62]++;	
	}
	if(((game_ram[game_ram[66]]<<(game_ram[64]*2))&0b11000000)==0b11000000){
		game_ram[63]++;	
	}
	if(((game_ram[game_ram[66]]<<(game_ram[64]*2))&0b11000000)==0b01000000){
		game_ram[62]--;	
	}
	if(((game_ram[game_ram[66]]<<(game_ram[64]*2))&0b11000000)==0b10000000){
		game_ram[63]--;	
	}
	game_ram[64]++; 
	if(game_ram[64]==4){
		game_ram[64]=0;
		game_ram[66]++;
	}
	if(game_ram[66] == 60){
		game_ram[66] = 0;
	}
}

void check_movement(void){
	if(read_button(4)==1){ //rigth
		game_ram[65] = 0b00000000;
	}
	if(read_button(3)==1){ //left
		game_ram[65] = 0b00000001;
	}
	if(read_button(2)==1){ //down
		game_ram[65] = 0b00000011;
	}
	if(read_button(1)==1){ //up
		game_ram[65] = 0b00000010;
	}
}


#endif