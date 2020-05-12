#include "mole.h" // handle moles image

mole::mole(SDL_Texture* Text, SDL_Rect Rect)
{
	currentimage = Text;
	rectangle = Rect;
	delay = 0;
}

mole::~mole()
{
	SDL_DestroyTexture(currentimage);
}