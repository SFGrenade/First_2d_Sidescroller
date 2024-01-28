/*
 * PowerBeamProjectile.h
 *
 *  Created on: 11.02.2017
 *      Author: SFG
 */

#ifndef POWERBEAMPROJECTILE_H_
#define POWERBEAMPROJECTILE_H_

#include "BaseProjectile.h"

namespace game {

class Level;

class PowerBeamProjectile : public BaseProjectile {
  public:
  PowerBeamProjectile( twoDPos from, twoDPos to, int64_t timeToLive );
  virtual ~PowerBeamProjectile();

  void compute( uint64_t msSinceLastFrame, SDL_Surface* screen, Level* level );
};

} /* namespace game */

#endif /* POWERBEAMPROJECTILE_H_ */
