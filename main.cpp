/*
 * main.cpp
 *
 *  Created on: 13.01.2017
 *      Author: SFG
 */

// Including our standard in-/output
using namespace std;
#include <iostream>
// Other headers
#include <stdint.h>
#include <string>
#include <string.h>
#include "pugiXML/pugixml.hpp"

// Include our overall Objects
#include "overallObjects.h"
// Other own headers
#include "HUD/Hud.h"
#include "Level/Map.h"
#include "Level/Level.h"
#include "Level/Tile.h"
#include "Level/TransitionTile.h"
#include "Level/WallTile.h"
#include "Level/WaterTile.h"
#include "Player/Player.h"
#include "RevolverList/RevolverList.h"
#include "MusicPlayer/BGMPlayer.h"

#include "Converter/Old2New.h"
#include "Converter/TGA2Old.h"

int main1(int argc, char* argv[]) {
	cout << "Converting Level #001 old to new version: " << old2New(".\\Maps\\Level001.xml") << endl;
	cout << "Converting Level #002 old to new version: " << old2New(".\\Maps\\Level002.xml") << endl;
	cout << "Converting Level #003 old to new version: " << old2New(".\\Maps\\Level003.xml") << endl;
	cout << "Converting Level #004 old to new version: " << old2New(".\\Maps\\Level004.xml") << endl;
	cout << "Converting Level #005 old to new version: " << old2New(".\\Maps\\Level005.xml") << endl;
	return 0;
}

int main(int argc, char* argv[]) {
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
		cerr << "SDL initialize error! " << SDL_GetError() << endl;
		return EXIT_FAILURE;
	}
	if (!IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) {
		cerr << "SDL_image initialize error! " << IMG_GetError() << endl;
	}
	if (!(Mix_Init(MIX_INIT_MP3) & MIX_INIT_MP3) || Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
		cerr << "SDL_mixer initialize error! " << Mix_GetError() << endl;
	}

	// Window creation
	window = SDL_CreateWindow("First Game Project", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (!window) {
		cerr << "Window creation error! " << SDL_GetError() << endl;
		return EXIT_FAILURE;
	}

	game::BGMPlayer* myBGMPlayer = new game::BGMPlayer();

	// Get the surface of the window
	windowScreen = SDL_GetWindowSurface((SDL_Window*) window);

	game::Map* myWorld = new game::Map(myBGMPlayer);
	myWorld->selectLevel(0);

	game::Player* myPlayer = new game::Player(7, 5, gridWidth - 2, gridWidth - 2);
	myWorld->getSelectedLevel()->setPlayer(myPlayer);

	game::Hud myHUD(myPlayer);

	// Quit flag
	bool quit = false;

	// Frame counter
	uint64_t frames = 0;
	uint64_t second = 0;

	// Event handler
	SDL_Event e;
	SDL_KeyboardEvent lastKey;

	SDL_Surface* levelSurface;

	myBGMPlayer->play();

	msLastFrame = SDL_GetTicks();
	while (!quit) {
		//Handle events on queue
		while (SDL_PollEvent(&e) != 0) {
			//User requests quit
			if (e.type == SDL_QUIT) {
				quit = true;
			} else if (e.type == SDL_WINDOWEVENT) {
				if (e.window.event == SDL_WINDOWEVENT_CLOSE && e.window.windowID == SDL_GetWindowID(window)) {
					quit = true;
				}
				msLastFrame = SDL_GetTicks();
			} else if (e.type == SDL_KEYDOWN) {
				if (e.key.keysym.sym != lastKey.keysym.sym) {
					if (e.key.keysym.sym == SDLK_ESCAPE) {
						quit = true;
					} else if (e.key.keysym.sym == SDLK_w) {
						myPlayer->setUp(true);
					} else if (e.key.keysym.sym == SDLK_s) {
						myPlayer->setDown(true);
					} else if (e.key.keysym.sym == SDLK_a) {
						myPlayer->setLeft(true);
					} else if (e.key.keysym.sym == SDLK_d) {
						myPlayer->setRight(true);
					} else if (e.key.keysym.sym == SDLK_UP) {
						myPlayer->rollWpnPrev();
					} else if (e.key.keysym.sym == SDLK_DOWN) {
						myPlayer->rollWpnNext();
					}
					lastKey = e.key;
				}
			} else if (e.type == SDL_KEYUP) {
				if (e.key.keysym.sym == SDLK_w) {
					myPlayer->setUp(false);
				} else if (e.key.keysym.sym == SDLK_s) {
					myPlayer->setDown(false);
				} else if (e.key.keysym.sym == SDLK_a) {
					myPlayer->setLeft(false);
				} else if (e.key.keysym.sym == SDLK_d) {
					myPlayer->setRight(false);
				}
				lastKey = *(new SDL_KeyboardEvent { });
			} else if (e.type == SDL_MOUSEWHEEL) {
				if (e.wheel.y == 1) {
					myPlayer->rollWpnPrev();
				} else {
					myPlayer->rollWpnNext();
				}
			} else if (e.type == SDL_MOUSEBUTTONDOWN) {
				myPlayer->onMouseButtonDown(e.button);
			} else if (e.type == SDL_MOUSEBUTTONUP) {
				myPlayer->onMouseButtonUp(e.button);
			}
		}
		// ---------------------------------------------------------------------------------------------------------------------------------

		myPlayer->updatePosition(msPassed, myWorld);
		myWorld->updateEntities(msPassed);

		// ---------------------------------------------------------------------------------------------------------------------------------

		// Fill the screen white
		SDL_FillRect((SDL_Surface*) windowScreen, NULL, 0xFF000000);

		// ---------------------------------------------------------------------------------------------------------------------------------
		myWorld->getSelectedLevel()->setPlayer(myPlayer);
		levelSurface = myWorld->getSelectedLevel()->getSurface();
		for (game::Weapon* weapon : myPlayer->getWeapons()) {
			weapon->compute(msPassed, levelSurface, myWorld->getSelectedLevel());
		}
		SDL_BlitScaled(levelSurface, myWorld->getSelectedLevel()->getViewRect(), (SDL_Surface*) windowScreen, NULL);
		// ---------------------------------------------------------------------------------------------------------------------------------

		SDL_BlitScaled(myHUD.getSurface(), NULL, (SDL_Surface*) windowScreen, NULL);

		// Update the now-filled screen
		SDL_UpdateWindowSurface((SDL_Window*) window);
		msPassed = SDL_GetTicks() - msLastFrame;
		msLastFrame = SDL_GetTicks();
		second += msPassed;
		frames++;
		if (second >= 1000) {
			SDL_SetWindowTitle(window, (std::to_string(frames) + std::string(" FPS")).c_str());
			second %= 1000;
			frames = 0;
		}
	}

	 // Destroy the window
	 SDL_FreeSurface((SDL_Surface*) windowScreen);
	 SDL_DestroyWindow((SDL_Window*) window);

	delete myPlayer;
	delete myBGMPlayer;
	delete myWorld;
	levelSurface = NULL;
	windowScreen = NULL;
	window = NULL;
	delete pixel;

	// Quit SDL
	Mix_Quit();
	IMG_Quit();
	SDL_Quit();
	return EXIT_SUCCESS;
}
