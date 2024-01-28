/*
 * DebugWeapon.cpp
 *
 *  Created on: 11.02.2017
 *      Author: SFG
 */

#include "DebugWeapon.h"

#include <iostream>


namespace game {

DebugWeapon::DebugWeapon( const char* pathToFile, const char* name, const char* shortDesc, const char* longDesc )
    : Weapon( pathToFile, name, shortDesc, longDesc ) {}

DebugWeapon::~DebugWeapon() {
  // this->~Weapon();
}

void DebugWeapon::shoot( twoDPos from, twoDPos to ) {}

void DebugWeapon::compute( uint64_t msSinceLastFrame, SDL_Surface* screen, Level* level ) {}

} /* namespace game */
