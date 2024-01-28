/*
 * Weapon.h
 *
 *  Created on: 03.02.2017
 *      Author: SFG
 */

#ifndef WEAPON_H_
#define WEAPON_H_

// Including SDL headers
#include <SDL2/SDL.h>
#include <vector>

#include "../overallObjects.h"
#include "Projectiles/BaseProjectile.h"


namespace game {

class Level;

class Weapon {
  protected:
  SDL_Surface* image;
  char* name;
  char* shortDesc;
  char* longDesc;

  std::vector< BaseProjectile* > projectiles;

  public:
  Weapon( const char* pathToFile, const char* name, const char* shortDesc, const char* longDesc );
  virtual ~Weapon();

  SDL_Surface* getImage();
  char* getName();
  char* getShortDesc();
  char* getLongDesc();

  virtual void shoot( twoDPos from, twoDPos to ) = 0;
  virtual void compute( uint64_t msSinceLastFrame, SDL_Surface* screen, Level* level ) = 0;
};

} /* namespace game */

#endif /* WEAPON_H_ */
