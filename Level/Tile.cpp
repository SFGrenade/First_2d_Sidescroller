/*
 * Tile.cpp
 *
 *  Created on: 27.01.2017
 *      Author: SFG
 */

#include "Tile.h"
#include "../Player/Player.h"

namespace game {

Tile::Tile(uint16_t tileType, uint32_t tileColor, int tileTerrainType) :
		mType(tileType), mColor(tileColor), mTerrainType((terrainType) tileTerrainType) {
}

Tile::~Tile() {
}

std::string Tile::toString() {
	std::string ret("Tile{Type:'");
	ret.append(std::to_string(mType));
	ret.append("', Color:'");
	ret.append(std::to_string(mColor));
	ret.append("', Type:'");
	ret.append(std::to_string(mTerrainType));
	ret.append("'}");
	return ret;
}

uint32_t Tile::getColor() {
	return mColor;
}

uint16_t Tile::getType() {
	return mType;
}

terrainType Tile::getTerrainType() {
	return mTerrainType;
}

} /* namespace game */
