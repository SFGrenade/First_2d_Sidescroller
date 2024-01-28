/*
 * MolecularBeam.h
 *
 *  Created on: 11.02.2017
 *      Author: SFG
 */

#ifndef MOLECULARBEAM_H_
#define MOLECULARBEAM_H_

#include "Weapon.h"

namespace game {

class MolecularBeam : public Weapon {
  public:
  MolecularBeam();
  virtual ~MolecularBeam();

  void shoot( twoDPos from, twoDPos to );
  void compute( uint64_t msSinceLastFrame, SDL_Surface* screen, Level* level );
};

} /* namespace game */

#endif /* MOLECULARBEAM_H_ */
