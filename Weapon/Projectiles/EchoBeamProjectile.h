/*
 * EchoBeamProjectile.h
 *
 *  Created on: 11.02.2017
 *      Author: SFG
 */

#ifndef ECHOBEAMPROJECTILE_H_
#define ECHOBEAMPROJECTILE_H_

#include "BaseProjectile.h"

namespace game {

class Level;

class EchoBeamProjectile : public BaseProjectile {
  public:
  EchoBeamProjectile( twoDPos from, twoDPos to, int64_t timeToLive );
  virtual ~EchoBeamProjectile();

  void compute( uint64_t msSinceLastFrame, SDL_Surface* screen, Level* level );
};

} /* namespace game */

#endif /* ECHOBEAMPROJECTILE_H_ */
