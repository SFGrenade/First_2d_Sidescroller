/*
 * AnnihilatorBeam.h
 *
 *  Created on: 11.02.2017
 *      Author: SFG
 */

#ifndef ANNIHILATORBEAM_H_
#define ANNIHILATORBEAM_H_

#include "Weapon.h"

namespace game {

class AnnihilatorBeam : public Weapon {
  public:
  AnnihilatorBeam();
  virtual ~AnnihilatorBeam();

  void shoot( twoDPos from, twoDPos to );
  void compute( uint64_t msSinceLastFrame, SDL_Surface* screen, Level* level );
};

} /* namespace game */

#endif /* ANNIHILATORBEAM_H_ */
