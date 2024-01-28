/*
 * IceBeam.h
 *
 *  Created on: 11.02.2017
 *      Author: SFG
 */

#ifndef ICEBEAM_H_
#define ICEBEAM_H_

#include "Weapon.h"

namespace game {

class IceBeam : public Weapon {
  public:
  IceBeam();
  virtual ~IceBeam();

  void shoot( twoDPos from, twoDPos to );
  void compute( uint64_t msSinceLastFrame, SDL_Surface* screen, Level* level );
};

} /* namespace game */

#endif /* ICEBEAM_H_ */
