/*
 * WaveBeamProjectile.h
 *
 *  Created on: 11.02.2017
 *      Author: SFG
 */

#ifndef WAVEBEAMPROJECTILE_H_
#define WAVEBEAMPROJECTILE_H_

#include "BaseProjectile.h"

namespace game {

class Level;

class WaveBeamProjectile : public BaseProjectile {
  public:
  WaveBeamProjectile( twoDPos from, twoDPos to, int64_t timeToLive );
  virtual ~WaveBeamProjectile();

  void compute( uint64_t msSinceLastFrame, SDL_Surface* screen, Level* level );
};

} /* namespace game */

#endif /* WAVEBEAMPROJECTILE_H_ */
