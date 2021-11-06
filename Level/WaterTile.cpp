/*
 * WaterTile.cpp
 *
 *  Created on: 10.02.2017
 *      Author: SFG
 */

#include "WaterTile.h"

namespace game {

WaterTile::WaterTile(uint16_t tileType, uint32_t tileColor, int tileTerrainType) :
		Tile(tileType, tileColor, tileTerrainType) {
}

WaterTile::~WaterTile() {
	this->~Tile();
}

void WaterTile::collide(Player* player, Map* map) {
}
void WaterTile::collideEntity(BaseEntity* entity, Map* map) {
}

void WaterTile::hit(DamageType damageType) {
}

std::string WaterTile::toString() {
	std::string ret("WaterTile{}");
	return ret;
}

} /* namespace game */
