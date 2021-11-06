/*
 * PowerBeam.h
 *
 *  Created on: 11.02.2017
 *      Author: SFG
 */

#ifndef POWERBEAM_H_
#define POWERBEAM_H_

#include "Weapon.h"

namespace game {

class PowerBeam: public Weapon {
public:
	PowerBeam();
	virtual ~PowerBeam();

	void shoot(twoDPos from, twoDPos to);
	void compute(uint64_t msSinceLastFrame, SDL_Surface* screen, Level* level);
};

} /* namespace game */

#endif /* POWERBEAM_H_ */
