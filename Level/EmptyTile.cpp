/*
 * EmptyTile.cpp
 *
 *  Created on: 10.02.2017
 *      Author: SFG
 */

#include "EmptyTile.h"

namespace game {

EmptyTile::EmptyTile() : Tile( 0, 0, TERRAINTYPE_EMPTY ) {}

EmptyTile::~EmptyTile() {
  // this->~Tile();
}

void EmptyTile::collide( Player* player, Map* map ) {}
void EmptyTile::collideEntity( BaseEntity* entity, Map* map ) {}

void EmptyTile::hit( DamageType damageType ) {}

std::string EmptyTile::toString() {
  std::string ret( "EmptyTile{}" );
  return ret;
}

} /* namespace game */
