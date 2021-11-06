/*
 * WallTile.h
 *
 *  Created on: 10.02.2017
 *      Author: SFG
 */

#ifndef WALLTILE_H_
#define WALLTILE_H_

#include "Tile.h"

namespace game {

class WallTile: public Tile {
public:
	WallTile(uint16_t tileType = 0, uint32_t tileColor = 0, int tileTerrainType = TERRAINTYPE_NORMAL);
	virtual ~WallTile();

	virtual std::string toString();

	void collide(Player* player, Map* map);
	void collideEntity(BaseEntity* entity, Map* map);
	void hit(DamageType damageType);
};

} /* namespace game */

#endif /* WALLTILE_H_ */
