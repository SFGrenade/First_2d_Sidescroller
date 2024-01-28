/*
 * PowerBeamProjectile.cpp
 *
 *  Created on: 11.02.2017
 *      Author: SFG
 */

#include "PowerBeamProjectile.h"

#include "../../Level/Level.h"
#include "../../Level/Tile.h"


namespace game {

PowerBeamProjectile::PowerBeamProjectile( twoDPos from, twoDPos to, int64_t timeToLive ) : BaseProjectile( from, to, timeToLive ) {}

PowerBeamProjectile::~PowerBeamProjectile() {
  // this->~BaseProjectile();
}

void PowerBeamProjectile::compute( uint64_t msSinceLastFrame, SDL_Surface* screen, Level* level ) {
  this->_timeToLive -= msSinceLastFrame;
  for( twoDPos toBePixel : this->line( _from, _to, screen ) ) {
    if( level->getTile( toBePixel.x / gridWidth, toBePixel.y / gridWidth )->getTerrainType() != TERRAINTYPE_EMPTY
        && level->getTile( toBePixel.x / gridWidth, toBePixel.y / gridWidth )->getTerrainType() != TERRAINTYPE_WATER ) {
      if( !_computed ) {
        level->getTile( toBePixel.x / gridWidth, toBePixel.y / gridWidth )->hit( DAMAGETYPE_POWERBEAM );
        _computed = true;
      }
      return;
    }
    pixel->x = (int)toBePixel.x;
    pixel->y = (int)toBePixel.y;
    SDL_FillRect( screen, pixel, 0xFFFF00FF );
  }
}

} /* namespace game */
