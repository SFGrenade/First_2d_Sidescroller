/*
 * SniperBeam.cpp
 *
 *  Created on: 11.02.2017
 *      Author: SFG
 */

#include "SniperBeam.h"

#include "../Level/Level.h"
#include "Projectiles/BaseProjectile.h"
#include "Projectiles/SniperBeamProjectile.h"


namespace game {

SniperBeam::SniperBeam() : Weapon( ".\\Img\\SniperBeam.png", "Sniper Beam", "The Sniper Beam", "Maybe it\'s the Sniper Beam" ) {}

SniperBeam::~SniperBeam() {
  // this->~Weapon();
}

void SniperBeam::shoot( twoDPos from, twoDPos to ) {
  this->projectiles.push_back( new SniperBeamProjectile( from, to, 500 ) );
}

void SniperBeam::compute( uint64_t msSinceLastFrame, SDL_Surface* screen, Level* level ) {
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
