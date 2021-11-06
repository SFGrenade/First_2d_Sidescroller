/*
 * WallTile.cpp
 *
 *  Created on: 10.02.2017
 *      Author: SFG
 */

#include <iostream>
#include "WallTile.h"

namespace game {

WallTile::WallTile(uint16_t tileType, uint32_t tileColor, int tileTerrainType) :
		Tile(tileType, tileColor, tileTerrainType) {
}

WallTile::~WallTile() {
	this->~Tile();
}

void WallTile::collide(Player* player, Map* map) {
}
void WallTile::collideEntity(BaseEntity* entity, Map* map) {
}

void WallTile::hit(DamageType damageType) {
}

std::string WallTile::toString() {
	std::string ret("WallTile{}");
	return ret;
}

} /* namespace game */
