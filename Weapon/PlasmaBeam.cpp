/*
 * PlasmaBeam.cpp
 *
 *  Created on: 11.02.2017
 *      Author: SFG
 */

#include "PlasmaBeam.h"

#include "../Level/Level.h"
#include "Projectiles/BaseProjectile.h"
#include "Projectiles/PlasmaBeamProjectile.h"


namespace game {

PlasmaBeam::PlasmaBeam() : Weapon( ".\\Img\\PlasmaBeam.png", "Plasma Beam", "The Plasma Beam", "Maybe it\'s the Plasma Beam" ) {}

PlasmaBeam::~PlasmaBeam() {
  ////this->~Weapon();
}

void PlasmaBeam::shoot( twoDPos from, twoDPos to ) {
  this->projectiles.push_back( new PlasmaBeamProjectile( from, to, 500 ) );
}

void PlasmaBeam::compute( uint64_t msSinceLastFrame, SDL_Surface* screen, Level* level ) {
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
