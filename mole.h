//class mole : control-render mole image and mole dissapear time.

#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
class mole
{
public:
	mole(SDL_Texture* Text, SDL_Rect Rect);
	~mole();

	SDL_Texture* currentimage;
	SDL_Rect rectangle;
	int delay;

};

