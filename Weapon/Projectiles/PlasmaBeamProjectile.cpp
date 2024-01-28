/*
 * PlasmaBeamProjectile.cpp
 *
 *  Created on: 11.02.2017
 *      Author: SFG
 */

#include "PlasmaBeamProjectile.h"

#include "../../Level/Level.h"
#include "../../Level/Tile.h"


namespace game {

PlasmaBeamProjectile::PlasmaBeamProjectile( twoDPos from, twoDPos to, int64_t timeToLive ) : BaseProjectile( from, to, timeToLive ) {}

PlasmaBeamProjectile::~PlasmaBeamProjectile() {
  // this->~BaseProjectile();
}

void PlasmaBeamProjectile::compute( uint64_t msSinceLastFrame, SDL_Surface* screen, Level* level ) {
  this->_timeToLive -= msSinceLastFrame;
  for( twoDPos toBePixel : this->line( _from, _to, screen ) ) {
    if( level->getTile( toBePixel.x / gridWidth, toBePixel.y / gridWidth )->getTerrainType() != TERRAINTYPE_EMPTY
        && level->getTile( toBePixel.x / gridWidth, toBePixel.y / gridWidth )->getTerrainType() != TERRAINTYPE_WATER ) {
      if( !_computed ) {
        level->getTile( toBePixel.x / gridWidth, toBePixel.y / gridWidth )->hit( DAMAGETYPE_PLASMABEAM );
        _computed = true;
      }
      return;
    }
    pixel->x = (int)toBePixel.x;
    pixel->y = (int)toBePixel.y;
    SDL_FillRect( screen, pixel, 0xFF4000FF );
  }
}

} /* namespace game */
