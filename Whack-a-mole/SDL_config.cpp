#include "SDL_config.h" // SDL.h and SDL_image.h are included in SDL_Config.h //
#include <iostream>
using namespace std;

SDL_config::SDL_config(bool* quit)
{
	SDL_Init(SDL_INIT_VIDEO);
	wind = nullptr;
	wind = SDL_CreateWindow("Shoot-a-mole", 100, 100, 640, 480, SDL_WINDOW_SHOWN);
		if (wind == nullptr)
		{
			cout << "Couldn't initialize window!!";
			*quit = true;
		}

	rend = nullptr;
	rend = SDL_CreateRenderer(wind, -1, SDL_RENDERER_ACCELERATED);

	evn = new SDL_Event();
}

SDL_config::~SDL_config()
{
	SDL_DestroyWindow(wind);
	SDL_DestroyRenderer(rend);
	
	delete evn;
	SDL_Quit();
}

SDL_Renderer* SDL_config::getRend()
{
	return rend;
}

SDL_Event* SDL_config::getEvent()
{
	return evn;
}
