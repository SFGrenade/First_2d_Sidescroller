/*
 * IceBeamProjectile.h
 *
 *  Created on: 11.02.2017
 *      Author: SFG
 */

#ifndef ICEBEAMPROJECTILE_H_
#define ICEBEAMPROJECTILE_H_

#include "BaseProjectile.h"

namespace game {

class Level;

class IceBeamProjectile: public BaseProjectile {
public:
	IceBeamProjectile(twoDPos from, twoDPos to, int64_t timeToLive);
	virtual ~IceBeamProjectile();

	void compute(uint64_t msSinceLastFrame, SDL_Surface* screen, Level* level);
};

} /* namespace game */

#endif /* ICEBEAMPROJECTILE_H_ */
