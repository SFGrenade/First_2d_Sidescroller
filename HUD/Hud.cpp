/*
 * Hud.cpp
 *
 *  Created on: 02.02.2017
 *      Author: SFG
 */

#include "Hud.h"
#include "../Player/Player.h"

namespace game {

Hud::Hud(Player* player) :
		mPlayer(player) {

	hudSurface = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32, 0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF);
	viewRect = &hudSurface->clip_rect;
	weaponRectCurr = new SDL_Rect { viewRect->w - (2 * gridWidth), viewRect->h - (3 * gridWidth), gridWidth, gridWidth };
	weaponRectNext = new SDL_Rect { viewRect->w - gridWidth, viewRect->h - (2 * gridWidth), gridWidth, gridWidth };
	weaponRectPrev = new SDL_Rect { viewRect->w - (3 * gridWidth), viewRect->h - (2 * gridWidth), gridWidth, gridWidth };
	minimapRect = new SDL_Rect { viewRect->w - (2 * gridWidth), 0, 2 * gridWidth, 2 * gridWidth };
	lifeRect = new SDL_Rect { 0, 0, 5 * gridWidth, 1 * gridWidth };
	ammoRect = new SDL_Rect { 0, viewRect->h - (2 * gridWidth), 3 * gridWidth, 2 * gridWidth };
}

Hud::~Hud() {
	SDL_FreeSurface(hudSurface);
	delete hudSurface;
	delete viewRect;
	mPlayer = NULL;

	delete weaponRectCurr;
	delete weaponRectNext;
	delete weaponRectPrev;

	delete minimapRect;
	delete lifeRect;
	delete ammoRect;
}

SDL_Surface* Hud::getSurface() {
	SDL_FillRect(hudSurface, NULL, 0x00000000);
	SDL_FillRect(hudSurface, minimapRect, 0xFFFFFFFF);
	SDL_FillRect(hudSurface, lifeRect, 0xFFFFFFFF);
	SDL_FillRect(hudSurface, ammoRect, 0xFFFFFFFF);

	SDL_BlitScaled(mPlayer->getWeapon(0)->getImage(), NULL, hudSurface, weaponRectCurr);
	SDL_BlitScaled(mPlayer->getWeapon(1)->getImage(), NULL, hudSurface, weaponRectNext);
	SDL_BlitScaled(mPlayer->getWeapon(-1)->getImage(), NULL, hudSurface, weaponRectPrev);

	return hudSurface;
}

} /* namespace game */
