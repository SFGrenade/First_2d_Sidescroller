/*
 * TransitionTile.h
 *
 *  Created on: 10.02.2017
 *      Author: SFG
 */

#ifndef TRANSITIONTILE_H_
#define TRANSITIONTILE_H_

#include "Tile.h"

class Player;

namespace game {

class Map;

class TransitionTile: public Tile {
protected:
	uint16_t toX, toY, levelTo;
public:
	TransitionTile(uint16_t xTo = 0, uint16_t yTo = 0, uint16_t levelIndexTo = 0, uint16_t tileType = 0, uint32_t tileColor = 0);
	virtual ~TransitionTile();

	virtual std::string toString();

	void collide(Player* player, Map* map);
	void collideEntity(BaseEntity* entity, Map* map);
	void hit(DamageType damageType);
};

} /* namespace game */

#endif /* TRANSITIONTILE_H_ */
