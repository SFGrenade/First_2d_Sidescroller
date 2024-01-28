/*
 * PlasmaBeamProjectile.h
 *
 *  Created on: 11.02.2017
 *      Author: SFG
 */

#ifndef PLASMABEAMPROJECTILE_H_
#define PLASMABEAMPROJECTILE_H_

#include "BaseProjectile.h"

namespace game {

class Level;

class PlasmaBeamProjectile : public BaseProjectile {
  public:
  PlasmaBeamProjectile( twoDPos from, twoDPos to, int64_t timeToLive );
  virtual ~PlasmaBeamProjectile();

  void compute( uint64_t msSinceLastFrame, SDL_Surface* screen, Level* level );
};

} /* namespace game */

#endif /* PLASMABEAMPROJECTILE_H_ */
