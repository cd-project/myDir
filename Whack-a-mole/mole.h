//class mole : control-render mole image and mole dissapear time.

#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
class mole
{
public:
	mole(SDL_Texture* genText, SDL_Rect* genRect);
	~mole();

	SDL_Texture* currentimage;
	SDL_Rect rectangle;
	int delay;

};

