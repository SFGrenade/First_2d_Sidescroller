/*
 * WaveBeamProjectile.cpp
 *
 *  Created on: 11.02.2017
 *      Author: SFG
 */

#include "WaveBeamProjectile.h"

#include "../../Level/Level.h"
#include "../../Level/Tile.h"


namespace game {

WaveBeamProjectile::WaveBeamProjectile( twoDPos from, twoDPos to, int64_t timeToLive ) : BaseProjectile( from, to, timeToLive ) {}

WaveBeamProjectile::~WaveBeamProjectile() {
  // this->~BaseProjectile();
}

void WaveBeamProjectile::compute( uint64_t msSinceLastFrame, SDL_Surface* screen, Level* level ) {
  uint16_t lastHit[2];
  this->_timeToLive -= msSinceLastFrame;
  for( twoDPos toBePixel : this->line( _from, _to, screen ) ) {
    if( !_computed ) {
      if( level->getTile( toBePixel.x / gridWidth, toBePixel.y / gridWidth )->getTerrainType() != TERRAINTYPE_EMPTY
          && level->getTile( toBePixel.x / gridWidth, toBePixel.y / gridWidth )->getTerrainType() != TERRAINTYPE_WATER ) {
        if( lastHit[0] != (uint16_t)toBePixel.x / gridWidth || lastHit[1] != (uint16_t)toBePixel.y / gridWidth ) {
          level->getTile( toBePixel.x / gridWidth, toBePixel.y / gridWidth )->hit( DAMAGETYPE_WAVEBEAM );
        }
        lastHit[0] = (uint16_t)toBePixel.x / gridWidth;
        lastHit[1] = (uint16_t)toBePixel.y / gridWidth;
      }
    }
    pixel->x = (int)toBePixel.x;
    pixel->y = (int)toBePixel.y;
    SDL_FillRect( screen, pixel, 0xC000FFFF );
  }
  _computed = true;
}

} /* namespace game */
