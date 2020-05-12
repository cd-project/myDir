#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

// this class accounts for window, renderer and event handler.
class SDL_config
{
public:
	SDL_config(bool* quit);
	~SDL_config();

	SDL_Renderer* getRend(); // day ne'
	SDL_Event* getEvent();

private:
	SDL_Window* wind;
	SDL_Renderer* rend;
	SDL_Event* evn;
};

