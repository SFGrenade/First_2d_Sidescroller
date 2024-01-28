/*
 * MolecularBeamProjectile.h
 *
 *  Created on: 11.02.2017
 *      Author: SFG
 */

#ifndef MOLECULARBEAMPROJECTILE_H_
#define MOLECULARBEAMPROJECTILE_H_

#include "BaseProjectile.h"

namespace game {

class Level;

class MolecularBeamProjectile : public BaseProjectile {
  public:
  MolecularBeamProjectile( twoDPos from, twoDPos to, int64_t timeToLive );
  virtual ~MolecularBeamProjectile();

  void compute( uint64_t msSinceLastFrame, SDL_Surface* screen, Level* level );
};

} /* namespace game */

#endif /* MOLECULARBEAMPROJECTILE_H_ */
