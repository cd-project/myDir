#pragma once
#include <string>
#include <SDL.h>
using namespace std;

class Window
{
	Window(const string& title, int width, int height);
	~Window();

private:
	bool init();

private:
	string _title;
	int _width = 1366;
	int _height = 768;

	bool _closed = false;
	SDL_Window* _window = nullptr;
};
