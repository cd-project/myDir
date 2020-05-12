#pragma once
#include "SDL_config.h"
#include "mole.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

class game
{
public:
	game();
	~game();
	void looper();
	int points;
	int misses;
	
private:
	bool quit; // keep game running
	
	int locator; // get coordinate of mouse-click, check if it's on a mole and which one

	int status; // game-state: 0=start, 1=gaming, 2=scoring

	int mode; //0=easy, 1=medium, 2=hard

	// Rectangle of points/misses counter, will be used by ShowText function.
	SDL_Rect pointsRect;
	SDL_Rect missesRect;
	
	// start menu GUI
	SDL_Texture* bkg; // background image
	SDL_Texture* high_box; // all-time highscore box.
	SDL_Rect bkgRect;		//
	SDL_Rect high_boxRect;
	SDL_Rect highRect;	// rectangle for background and all-time high score...

	// points counter image load
	SDL_Texture* pts;
	SDL_Rect ptsRect;

	// misses counter image load
	SDL_Texture* miss;
	SDL_Rect missRect;

	// background ingame image load
	SDL_Texture* igbkg;
	SDL_Rect igRect;

	// ingame music
	Mix_Music* bkgmusic; // while status=0
	Mix_Music* igmusic;  // while status=1, playing 
	Mix_Chunk* eff;		 // hit sound effect
	Mix_Chunk* loseeff;  // game-loss sound effect
	
	// moles graphic info
	SDL_Texture* hid[6]; // hidden moles
	SDL_Texture* rev[6]; // revealed moles
	SDL_Texture* hit[6]; // blown moles

	//	Store moles info (pos, status, etc)
	mole* moles[6];

	// graphic info for score page
	int theHighS; // highscore of all time, saved in hs.txt
	bool newHighS; // check if points scored is a new high score or not
	SDL_Texture* ptsBox; // after loss box, show points scored and Highest score.
	SDL_Texture* newHigh; // image effect if player scored a new high score.
	
	SDL_Texture* again; // try again box
	SDL_Rect ptsBoxRect; //rectangle for these above
	SDL_Rect newHighRect;
	SDL_Rect yourptsRect;
	SDL_Rect bestRect; 
	SDL_Rect againRect;

	// SDL renderer and event handler
	SDL_config* config;
};
