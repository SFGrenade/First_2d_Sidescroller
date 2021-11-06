/*
 * Hud.h
 *
 *  Created on: 02.02.2017
 *      Author: SFG
 */

#ifndef HUD_H_
#define HUD_H_

// Including SDL headers
#include <SDL2/SDL.h>

#include "../overallObjects.h"

namespace game {

class Player;

class Hud {
private:
	SDL_Surface* hudSurface;
	SDL_Rect* viewRect;
	game::Player* mPlayer;

	SDL_Rect* weaponRectCurr;
	SDL_Rect* weaponRectNext;
	SDL_Rect* weaponRectPrev;
	SDL_Rect* minimapRect;
	SDL_Rect* lifeRect;
	SDL_Rect* ammoRect;
public:
	Hud(Player* player);
	virtual ~Hud();

	SDL_Surface* getSurface();
};

} /* namespace game */

#endif /* HUD_H_ */
