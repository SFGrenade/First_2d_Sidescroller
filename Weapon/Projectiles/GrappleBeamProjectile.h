/*
 * GrappleBeamProjectile.h
 *
 *  Created on: 11.02.2017
 *      Author: SFG
 */

#ifndef GRAPPLEBEAMPROJECTILE_H_
#define GRAPPLEBEAMPROJECTILE_H_

#include "BaseProjectile.h"

namespace game {

class Level;

class GrappleBeamProjectile: public BaseProjectile {
public:
	GrappleBeamProjectile(twoDPos from, twoDPos to, int64_t timeToLive);
	virtual ~GrappleBeamProjectile();

	void compute(uint64_t msSinceLastFrame, SDL_Surface* screen, Level* level);
};

} /* namespace game */

#endif /* GRAPPLEBEAMPROJECTILE_H_ */
