/*
 * SniperBeamProjectile.h
 *
 *  Created on: 11.02.2017
 *      Author: SFG
 */

#ifndef SNIPERBEAMPROJECTILE_H_
#define SNIPERBEAMPROJECTILE_H_

#include "BaseProjectile.h"

namespace game {

class Level;

class SniperBeamProjectile : public BaseProjectile {
  public:
  SniperBeamProjectile( twoDPos from, twoDPos to, int64_t timeToLive );
  virtual ~SniperBeamProjectile();

  void compute( uint64_t msSinceLastFrame, SDL_Surface* screen, Level* level );
};

} /* namespace game */

#endif /* SNIPERBEAMPROJECTILE_H_ */
