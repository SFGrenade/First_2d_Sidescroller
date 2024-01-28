/*
 * GrappleBeam.h
 *
 *  Created on: 11.02.2017
 *      Author: SFG
 */

#ifndef GRAPPLEBEAM_H_
#define GRAPPLEBEAM_H_

#include "Weapon.h"

namespace game {

class GrappleBeam : public Weapon {
  public:
  GrappleBeam();
  virtual ~GrappleBeam();

  void shoot( twoDPos from, twoDPos to );
  void compute( uint64_t msSinceLastFrame, SDL_Surface* screen, Level* level );
};

} /* namespace game */

#endif /* GRAPPLEBEAM_H_ */
