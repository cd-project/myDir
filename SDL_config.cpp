
#include "SDL_config.h" // SDL.h and SDL_image.h are included in SDL_Config.h //
#include <iostream>
using namespace std;

SDL_config::SDL_config(bool* quit)
{
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Init(SDL_INIT_AUDIO);
	TTF_Init();
	if (TTF_Init() < 0)
	{
		cout << "Couldn't initialize TrueType Font";
		*quit = true;
	}
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1)
	{
		cerr << "Mixer Initialization failed: " << Mix_GetError() << endl;
	}
	
	// create window
	wind = nullptr;
	wind = SDL_CreateWindow("Whack-a-mole", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 960, 540, SDL_WINDOW_SHOWN);
		if (wind == nullptr)
		{
			cout << "Couldn't initialize window!!";
			*quit = true;
		}
	// create renderer 
	rend = nullptr;
	rend = SDL_CreateRenderer(wind, -1, SDL_RENDERER_ACCELERATED);

	// create event container
	evn = new SDL_Event();
	
}

SDL_config::~SDL_config() // deconstructor
{
	SDL_DestroyWindow(wind);
	SDL_DestroyRenderer(rend);
	TTF_Quit();
	delete evn;
	SDL_Quit();
	Mix_CloseAudio();
}

SDL_Renderer* SDL_config::getRend() 
{
	return rend;
}

SDL_Event* SDL_config::getEvent()
{
	return evn;
}
