/*
 * Level.h
 *
 *  Created on: 27.01.2017
 *      Author: SFG
 */

#ifndef LEVEL_H_
#define LEVEL_H_

// Including SDL headers
#include <SDL2/SDL.h>

#include <stdint.h>
#include <string>
#include <vector>
#include "../overallObjects.h"

namespace game {

class Tile;
class TransitionTile;
class Player;
class BaseEntity;

class Level {
private:
	std::vector<std::vector<Tile*> > tilemap;
	SDL_Surface* levelSurface;
	SDL_Surface* finalSurface;
	SDL_Rect* viewRect;
	SDL_Rect* oldPlayerPos;
	game::Player* mPlayer;
	std::vector<BaseEntity*> entities;
	bool drawn;
public:
	Level(uint16_t w = 0, uint16_t h = 0);
	virtual ~Level();

	std::string toString();
	Tile* getTile(uint16_t x, uint16_t y);
	void setTile(uint16_t x, uint16_t y, Tile* tile);

	void setOuterBorder(Tile* tile);
	void fillRect(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, Tile* tile);

	void setPlayer(game::Player* player);

	SDL_Surface* getSurface();
	SDL_Rect* getViewRect();
	uint32_t getW();
	uint32_t getH();

	void addEntity(BaseEntity* newEntity);
	void updateEntities();
	std::vector<BaseEntity*> getEntities();
};

} /* namespace game */

#endif /* LEVEL_H_ */
