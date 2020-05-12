#include<iostream>
#include "game.h"
// redefinition of main function in SDL_main  
//so I have to undefine that main function before the program jump to the real entry point main below.
// this solution is provided by Stack Overflow.
#undef main 
int main(int argc, char* args[])
{
	game init;
	init.looper(); // game loop

	return 0;
}