#include "mole.h"

mole::mole(SDL_Texture* genText, SDL_Rect* genRect)
{
	currentimage = genText;
	rectangle = genRect;
	delay = 0;
}

mole::~mole()
{
	SDL_DestroyTexture(currentimage);
}