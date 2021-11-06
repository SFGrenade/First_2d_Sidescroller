/*
 * AnnihilatorBeamProjectile.h
 *
 *  Created on: 11.02.2017
 *      Author: SFG
 */

#ifndef ANNIHILATORBEAMPROJECTILE_H_
#define ANNIHILATORBEAMPROJECTILE_H_

#include "BaseProjectile.h"

namespace game {

class Level;

class AnnihilatorBeamProjectile: public BaseProjectile {
public:
	AnnihilatorBeamProjectile(twoDPos from, twoDPos to, int64_t timeToLive);
	virtual ~AnnihilatorBeamProjectile();

	void compute(uint64_t msSinceLastFrame, SDL_Surface* screen, Level* level);
};

} /* namespace game */

#endif /* ANNIHILATORBEAMPROJECTILE_H_ */
