/*
 * WaveBeam.h
 *
 *  Created on: 11.02.2017
 *      Author: SFG
 */

#ifndef WAVEBEAM_H_
#define WAVEBEAM_H_

#include "Weapon.h"

namespace game {

class WaveBeam : public Weapon {
  public:
  WaveBeam();
  virtual ~WaveBeam();

  void shoot( twoDPos from, twoDPos to );
  void compute( uint64_t msSinceLastFrame, SDL_Surface* screen, Level* level );
};

} /* namespace game */

#endif /* WAVEBEAM_H_ */
