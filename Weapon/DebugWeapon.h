/*
 * DebugWeapon.h
 *
 *  Created on: 11.02.2017
 *      Author: SFG
 */

#ifndef DEBUGWEAPON_H_
#define DEBUGWEAPON_H_

#include "Weapon.h"

namespace game {

class DebugWeapon : public Weapon {
  public:
  DebugWeapon( const char* pathToFile, const char* name, const char* shortDesc, const char* longDesc );
  virtual ~DebugWeapon();

  void shoot( twoDPos from, twoDPos to );
  void compute( uint64_t msSinceLastFrame, SDL_Surface* screen, Level* level );
};

} /* namespace game */

#endif /* DEBUGWEAPON_H_ */
