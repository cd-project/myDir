#include "game.h"
#include <iostream>
#include <string>

using namespace std;

// function to init new Rect
SDL_Rect createRect(int x, int y, int w, int h)
{
	SDL_Rect r;
	r.x = x;
	r.y = y;
	r.w = w;
	r.h = h;
	return r;
}

int locatorMole(int x, int y) // this function returns the number of the mole clicked on based on mouse click coordinate.
{
	if (y >= 143 and y <= 303)
	{
		if (x >= 98 and x <= 274)
		{
			return 0;
		}
		else if (x >= 381 and x <= 551)
		{
			return 2;
		}
		else if (x >= 666 and x <= 843)
		{
			return 4;
		}
	}
	else if (y >= 360 and y <= 500)
	{
		if (x >= 98 and x <= 272)
		{
			return 1;
		}
		else if (x >= 390 and x <= 558)
		{
			return 3;
		}
		else if (x >= 672 and x <= 843)
		{
			return 5;
		}
	}
}
// ShowText: render TrueType font /////
void ShowText(const char* text, SDL_Color fg, SDL_Renderer* renderer, int c_size, SDL_Rect& posit)
{
	TTF_Font* font = NULL;
	SDL_Surface* surface = NULL;
	SDL_Texture* texture = NULL;
	font = TTF_OpenFont("Arial.ttf", c_size);
	if (font == NULL)
	{
		cerr << "TTF_OpenFont() failed: " << TTF_GetError() << endl;
	}
	surface = TTF_RenderText_Blended(font, text, fg);
	texture = SDL_CreateTextureFromSurface(renderer, surface);

	SDL_FreeSurface(surface);
	TTF_SizeText(font, text, &posit.w, &posit.h);
	SDL_RenderCopy(renderer, texture, NULL, &posit);

	SDL_DestroyTexture(texture);
	TTF_CloseFont(font);
}

void PlayMusic(Mix_Music* music) // play long music
{
	Mix_PlayMusic(music, -1); // forever loop
}
game::game()
{
	quit = false; // if = true , game quit.
	status = 0;
	config = new SDL_config(&quit);


	// load background
	bkg = nullptr;
	bkg = IMG_LoadTexture(config->getRend(), "bg.png");
	if (bkg == nullptr)
	{
		cout << "Error!! Couldn't load background!" << endl;
		quit = true;
	}
	bkgRect = createRect(0, 0, 960, 540);

	high_box = IMG_LoadTexture(config->getRend(), "high_box.png");
	if (high_box == nullptr)
	{
		cout << "Error!! Couldn't load highscore box!!" << endl;
		quit = true;
	}
	high_boxRect = createRect(682, 5, 163, 45);
	highRect = createRect(870, 0, 60, 45);
	//load ingame background

	igbkg = nullptr;
	igbkg = IMG_LoadTexture(config->getRend(), "ingamebkg.png");
	if (igbkg == nullptr)
	{
		cout << "Error!! Couldn't load ingame background" << endl;
		quit = true;
	}

	igRect = createRect(0, 0, 960, 540);

	for (int i = 0; i < 6; i++)
	{
		hid[i] = nullptr;
	}
	// load background music
	bkgmusic = Mix_LoadMUS("strtmu.wav");
	if (bkgmusic == NULL)
	{
		cerr << "Mix_LoadMUS: " << Mix_GetError() << endl;
		quit = true;
	}

	// load ingame music
	igmusic = Mix_LoadMUS("igmu.wav");
	if (igmusic == NULL)
	{
		cerr << "Mix_LoadMUS: " <<  Mix_GetError() << endl;
		quit = true;
	}
	eff = Mix_LoadWAV("BAZOOKA.wav");
	if (eff == NULL)
	{
		cerr << "Mix_LoadWAV: " << Mix_GetError() << endl;
		quit = true;
	}
	loseeff = Mix_LoadWAV("loseeff.wav");
	if (loseeff == NULL)
	{
		cerr << "Mix_LoadWAV: " << Mix_GetError() << endl;
		quit = true;
	}
	hid[0] = IMG_LoadTexture(config->getRend(), "hid_0.png");
	if (hid[0] == nullptr)
	{
		cout << "Error!! Couldn't load hidden mole 0";
		quit = true;
	}

	hid[1] = IMG_LoadTexture(config->getRend(), "hid_1.png");
	if (hid[1] == nullptr)
	{
		cout << "Error!! Couldn't load hidden mole 1";
		quit = true;
	}

	hid[2] = IMG_LoadTexture(config->getRend(), "hid_2.png");
	if (hid[2] == nullptr)
	{
		cout << "Error!! Couldn't load hidden mole 2";
		quit = true;
	}

	hid[3] = IMG_LoadTexture(config->getRend(), "hid_3.png");
	if (hid[3] == nullptr)
	{
		cout << "Error!! Couldn't load hidden mole 3";
		quit = true;
	}

	hid[4] = IMG_LoadTexture(config->getRend(), "hid_4.png");
	if (hid[2] == nullptr)
	{
		cout << "Error!! Couldn't load hidden mole 4";
		quit = true;
	}

	hid[5] = IMG_LoadTexture(config->getRend(), "hid_5.png");
	if (hid[5] == nullptr)
	{
		cout << "Error!! Couldn't load hidden mole 5";
		quit = true;
	}

	for (int i = 0; i < 6; i++)
	{
		rev[i] = nullptr;
	}

	rev[0] = IMG_LoadTexture(config->getRend(), "rev_0.png");
	if (rev[0] == nullptr)
	{
		cout << "Error!! Couldn't load revealed mole 0";
		quit = true;
	}

	rev[1] = IMG_LoadTexture(config->getRend(), "rev_1.png");
	if (rev[1] == nullptr)
	{
		cout << "Error!! Couldn't load revealed mole 1";
		quit = true;
	}

	rev[2] = IMG_LoadTexture(config->getRend(), "rev_2.png");
	if (rev[2] == nullptr)
	{
		cout << "Error!! Couldn't load revealed mole 2";
		quit = true;
	}

	rev[3] = IMG_LoadTexture(config->getRend(), "rev_3.png");
	if (rev[3] == nullptr)
	{
		cout << "Error!! Couldn't load revealed mole 3";
		quit = true;
	}

	rev[4] = IMG_LoadTexture(config->getRend(), "rev_4.png");
	if (rev[4] == nullptr)
	{
		cout << "Error!! Couldn't load revealed mole 4";
		quit = true;
	}

	rev[5] = IMG_LoadTexture(config->getRend(), "rev_5.png");
	if (rev[5] == nullptr)
	{
		cout << "Error!! Couldn't load revealed mole 5";
		quit = true;
	}


	// hit animation ///////////////////////////////////////////////////////////////////////////////////////////////
	for (int i = 0; i < 6; i++)
	{
		hit[i] = nullptr;
	}

	hit[0] = IMG_LoadTexture(config->getRend(), "hit_0.png");
	if (hit[0] == nullptr)
	{
		cout << "Error!! Couldn't load hit mole 0";
		quit = true;
	}

	hit[1] = IMG_LoadTexture(config->getRend(), "hit_1.png");
	if (hit[1] == nullptr)
	{
		cout << "Error!! Couldn't load hit mole 1";
		quit = true;
	}

	hit[2] = IMG_LoadTexture(config->getRend(), "hit_2.png");
	if (hit[1] == nullptr)
	{
		cout << "Error!! Couldn't load hit mole 2";
		quit = true;
	}

	hit[3] = IMG_LoadTexture(config->getRend(), "hit_3.png");
	if (hit[3] == nullptr)
	{
		cout << "Error!! Couldn't load hit mole 3";
		quit = true;
	}

	hit[4] = IMG_LoadTexture(config->getRend(), "hit_4.png");
	if (hit[4] == nullptr)
	{
		cout << "Error!! Couldn't load hit mole 4";
		quit = true;
	}

	hit[5] = IMG_LoadTexture(config->getRend(), "hit_5.png");
	if (hit[5] == nullptr)
	{
		cout << "Error!! Couldn't load hit mole 5";
		quit = true;
	}

	moles[0] = new mole(hid[0], createRect(83, 137, 195, 187));
	moles[1] = new mole(hid[1], createRect(80, 329, 209, 193));
	moles[2] = new mole(hid[2], createRect(364, 130, 208, 185));
	moles[3] = new mole(hid[3], createRect(354, 329, 236, 194));
	moles[4] = new mole(hid[4], createRect(636, 117, 229, 191));
	moles[5] = new mole(hid[5], createRect(640, 320, 228, 196));

	pts = nullptr;
	pts = IMG_LoadTexture(config->getRend(), "pts_text.png");
	if (pts == nullptr)
	{
		cout << "Error!! Couldn't load points counter image" << endl;
		quit = true;
	}
	ptsRect = createRect(746, 0, 127, 39);

	miss = nullptr;
	miss = IMG_LoadTexture(config->getRend(), "miss_text.png");
	if (miss == nullptr)
	{
		cout << "Error!! Couldn't load misses counter image" << endl;
		quit = true;
	}
	missRect = createRect(748, 40, 124, 39);


	ptsBox = nullptr; // after-loss appearance
	ptsBox = IMG_LoadTexture(config->getRend(), "ptsBox.png");
	if (ptsBox == nullptr)
	{
		cout << "Error!! Couldn't load ptsBox" << endl;
		quit = true;
	}

	ptsBoxRect = createRect(242, 94, 455, 290);

	again = nullptr;
	again = IMG_LoadTexture(config->getRend(), "again.png");
	if (again == nullptr)
	{
		cout << "Error!! Couldn't load again button image" << endl;
		quit = true;
	}
	againRect = createRect(330, 404, 265, 98);

	yourptsRect = createRect(440, 155, 145, 50);
	bestRect = createRect(440, 284, 145, 55);


	newHigh = nullptr;
	newHigh = IMG_LoadTexture(config->getRend(), "new.png"); // test section
	if (newHigh == nullptr)
	{
		cout << "Error!! Couldn't load new highscore image!!" << endl;
		quit = true;
	}
	newHighRect = createRect(800, 400, 100, 32); // test section
	
	pointsRect = createRect(893, 1, 40, 39); // Rectangle for TTF
	
	missesRect = createRect(892, 40, 40, 39);// Rectangle for TTF

	// loads highscore from hs.txt.
	if (ifstream("hs.txt"))
	{
		string line;
		ifstream hsf("hs.txt");
		hsf >> theHighS;
		hsf.close();
	}
	else
	{
		theHighS = 0;
	}
}

game::~game()
{
	SDL_DestroyTexture(bkg);
	for (int i = 0; i < 6; i++)
	{
		SDL_DestroyTexture(hid[i]);
	}
	for (int i = 0; i < 6; i++)
	{
		SDL_DestroyTexture(rev[i]);
	}
	for (int i = 0; i < 6; i++)
	{
		SDL_DestroyTexture(hit[i]);
	}
	if (ifstream("hs.txt"))
	{
		remove("hs.txt");
	}

	ofstream hsFile("hs.txt");
	hsFile << theHighS;
}

void game::looper()
{
	
	SDL_Color fg = { 100,100,230 }; // ingame points color
	SDL_Color aflos = { 25, 125, 235 }; // after-loss points color
	SDL_Color yel = { 255,255,0 }; // yellow
	int txt_size = 30; 
	int aflose_size = 50;
	int spd0 = 500; // speed of moles while mode=0
	int spd1 = 300; // speed of moles while mode=1
	int spd2 = 175; // speed of moles while mode=2

	while (!quit and config->getEvent()->type != SDL_QUIT) // start point
	{
		
		if (Mix_PlayingMusic() == 0)
		{
			PlayMusic(bkgmusic); // play background music
		}
		
		// Clear up everything
		SDL_RenderClear(config->getRend());

		// background
		SDL_RenderCopy(config->getRend(), bkg, nullptr, &bkgRect);
		SDL_RenderCopy(config->getRend(), high_box, nullptr, &high_boxRect);
		ShowText(to_string(theHighS).c_str(), yel, config->getRend(), aflose_size, highRect);
		while (SDL_PollEvent(config->getEvent()))
		// detect mouse-click on which mode
		{
			if (config->getEvent()->type == SDL_MOUSEBUTTONDOWN)
			{
				if (config->getEvent()->motion.x > 685 and config->getEvent()->motion.x < 852 and
					config->getEvent()->motion.y > 88 and config->getEvent()->motion.y < 143) // easy mode button)
				{
					mode = 0;
					if (status == 0)
					{
						newHighS = false;
						status = 1;
						points = 0;
						misses = 0;
						PlayMusic(igmusic);
					}
				}
			if (config->getEvent()->motion.x > 645 and config->getEvent()->motion.x < 902 and
					config->getEvent()->motion.y > 233 and config->getEvent()->motion.y < 293) // medium mode button)
				{
					mode = 1;
					if (status == 0)
					{
						newHighS = false;
						status = 1;
						points = 0;
						misses = 0;
						PlayMusic(igmusic);
						
					}
				}
			if (config->getEvent()->motion.x > 683 and config->getEvent()->motion.x < 864 and
				config->getEvent()->motion.y > 374 and config->getEvent()->motion.y < 431) // hard mode button)
				{
					mode = 2;
					if (status == 0)
					{
						newHighS = false;
						status = 1;
						points = 0;
						misses = 0;
						PlayMusic(igmusic);
					}
				}
			}
		}
		// game has begun

		if (status == 1)
		{
			
			SDL_RenderCopy(config->getRend(), igbkg, nullptr, &igRect); // render ingame background
			SDL_RenderCopy(config->getRend(), pts, nullptr, &ptsRect);  // render point counter
			SDL_RenderCopy(config->getRend(), miss, nullptr, &missRect); // render misses counter

			
			ShowText(to_string(misses).c_str(), fg, config->getRend(), txt_size, missesRect);
			ShowText(to_string(points).c_str(), fg, config->getRend(), txt_size, pointsRect);




			// handle the moles
			for (int i = 0; i < 6; i++)
			{
				// if mole status is hidden, randomly decide if it should be revealed
				if (moles[i]->currentimage == hid[i])
				{
					if (rand() % 500 + 1 == 1)
					{
						moles[i]->currentimage = rev[i]; // reveal the "i" mole
						if(mode==0)
						{
							moles[i]->delay = spd0;
						}
						else if (mode == 1)
						{
							moles[i]->delay = spd1;
						}
						else if (mode == 2)
						{
							moles[i]->delay = spd2;
						}
						 // mole appears in spd0, spd1, spd2 millisecond, based on mode.
					}
				}
				else
				{
					// if delay time is over, moles have to be hidden again and plus one misses point.
					if (moles[i]->delay == 0)
					{
						// and mole hasn't been hit
						if (moles[i]->currentimage == rev[i])
						{
							misses++;
							
							ShowText(to_string(misses).c_str(), fg, config->getRend(), txt_size, missesRect);
							if (misses == 10) // game over if misses touch 10.
							{
								status = 2;
								Mix_PlayChannel(-1,loseeff,0);
								Mix_HaltMusic();
							}
						}
						// return to ground squad
						moles[i]->currentimage = hid[i];
					}
					else
					{
						moles[i]->delay--; // moles won't dissappear without this.
					}
				}
				SDL_RenderCopy(config->getRend(), moles[i]->currentimage, nullptr, &(moles[i]->rectangle)); // render moles
				
			}
			// detect mouse-click to see if a mole was clicked
			if (config->getEvent()->type == SDL_MOUSEBUTTONDOWN)
			{		
				locator = locatorMole(config->getEvent()->motion.x, config->getEvent()->motion.y);
				if(locator>=0 and locator<=5)
				{
					if (moles[locator]->currentimage == rev[locator])
					{	
						points++;
						misses--;
						ShowText(to_string(points).c_str(), fg, config->getRend(), txt_size, pointsRect);
						Mix_PlayChannel(-1, eff, 0);
						moles[locator]->currentimage = hit[locator];
						moles[locator]->delay = 100;
					}
				}
			}
		}
		else if (status == 2) // status = 2 , after game-loss
		{
			// render the after-loss score box
			SDL_RenderCopy(config->getRend(), ptsBox, nullptr, &ptsBoxRect);
			if (points > theHighS) // high score is loaded directly from hs.txt when the game started.
			{
				theHighS = points;
				newHighS = true;
			}
			ShowText(to_string(points).c_str(), aflos, config->getRend(), aflose_size, yourptsRect);
			ShowText(to_string(theHighS).c_str(), aflos, config->getRend(), aflose_size, bestRect);
			if (newHighS)
			{
				SDL_RenderCopy(config->getRend(), newHigh, nullptr, &newHighRect);
			}
			// try again box
			SDL_RenderCopy(config->getRend(), again, nullptr, &againRect);

			// detect if try again box was clicked
			if (config->getEvent()->type == SDL_MOUSEBUTTONDOWN)
			{
				if (config->getEvent()->motion.x >= 347 and config->getEvent()->motion.x <= 612 and
					config->getEvent()->motion.y >= 406 and config->getEvent()->motion.y <= 502)
				{
					status = 0;
					PlayMusic(bkgmusic);
					points = 0;
					misses = 0;
					newHighS = false;
				}
			}
		}
		SDL_RenderPresent(config->getRend()); // update the screen with rendering performed.
	}
}