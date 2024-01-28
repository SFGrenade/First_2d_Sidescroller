/*
 * WaveBeam.cpp
 *
 *  Created on: 11.02.2017
 *      Author: SFG
 */

#include "WaveBeam.h"

#include "../Level/Level.h"
#include "Projectiles/BaseProjectile.h"
#include "Projectiles/WaveBeamProjectile.h"


namespace game {

WaveBeam::WaveBeam() : Weapon( ".\\Img\\WaveBeam.png", "Wave Beam", "The Wave Beam", "Maybe it\'s the Wave Beam" ) {}

WaveBeam::~WaveBeam() {
  // this->~Weapon();
}

void WaveBeam::shoot( twoDPos from, twoDPos to ) {
  this->projectiles.push_back( new WaveBeamProjectile( from, to, 500 ) );
}

void WaveBeam::compute( uint64_t msSinceLastFrame, SDL_Surface* screen, Level* level ) {
  uint16_t i = 0;
  for( BaseProjectile* value : projectiles ) {
    if( value->alive() != true ) {
      projectiles.erase( projectiles.begin() + i );
    } else {
      value->compute( msSinceLastFrame, screen, level );
      i++;
    }
  }
}

} /* namespace game */
