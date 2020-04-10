#include "windows.h"
#include <SDL.h>
#include <iostream>
using namespace std;
Window::Window(const string& title, int width, int height) :
	_title(title), _width(width), _height(height)
{

}
Window::~Window()
{

}

bool Window::init()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		cout << "Failed to initialize!";
		return 0;
	}

	_window = SDL_CreateWindow(
		_title.c_str(),
	SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		_width, _height,
		0
		);

	
	


}