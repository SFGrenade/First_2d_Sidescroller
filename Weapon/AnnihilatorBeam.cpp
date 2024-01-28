/*
 * AnnihilatorBeam.cpp
 *
 *  Created on: 11.02.2017
 *      Author: SFG
 */

#include "AnnihilatorBeam.h"

#include "../Level/Level.h"
#include "Projectiles/AnnihilatorBeamProjectile.h"
#include "Projectiles/BaseProjectile.h"


namespace game {

AnnihilatorBeam::AnnihilatorBeam() : Weapon( ".\\Img\\AnnihilatorBeam.png", "Annihilator Beam", "The Annihilator Beam", "Maybe it\'s the Annihilator Beam" ) {}

AnnihilatorBeam::~AnnihilatorBeam() {
  ////this->~Weapon();
}

void AnnihilatorBeam::shoot( twoDPos from, twoDPos to ) {
  this->projectiles.push_back( new AnnihilatorBeamProjectile( from, to, 500 ) );
}

void AnnihilatorBeam::compute( uint64_t msSinceLastFrame, SDL_Surface* screen, Level* level ) {
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
