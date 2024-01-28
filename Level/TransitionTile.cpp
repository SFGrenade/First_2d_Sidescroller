/*
 * TransitionTile.cpp
 *
 *  Created on: 10.02.2017
 *      Author: SFG
 */

#include "TransitionTile.h"

#include "../Player/Player.h"
#include "Level.h"
#include "Map.h"


namespace game {

TransitionTile::TransitionTile( uint16_t xTo, uint16_t yTo, uint16_t levelIndexTo, uint16_t tileType, uint32_t tileColor )
    : Tile( tileType, tileColor, TERRAINTYPE_NORMAL ), toX( xTo ), toY( yTo ), levelTo( levelIndexTo ) {}

TransitionTile::~TransitionTile() {
  // this->~Tile();
}

void TransitionTile::collide( Player* player, Map* map ) {
  map->selectLevel( levelTo );
  map->getSelectedLevel()->setPlayer( player );
  player->setPos( (double)toX * gridWidth, (double)toY * gridWidth );
}
void TransitionTile::collideEntity( BaseEntity* entity, Map* map ) {}

void TransitionTile::hit( DamageType damageType ) {}

std::string TransitionTile::toString() {
  std::string ret( "TransitionTile{}" );
  return ret;
}

} /* namespace game */
