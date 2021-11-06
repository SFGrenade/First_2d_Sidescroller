/*
 * PlasmaBeam.h
 *
 *  Created on: 11.02.2017
 *      Author: SFG
 */

#ifndef PLASMABEAM_H_
#define PLASMABEAM_H_

#include "Weapon.h"

namespace game {

class PlasmaBeam: public Weapon {
public:
	PlasmaBeam();
	virtual ~PlasmaBeam();

	void shoot(twoDPos from, twoDPos to);
	void compute(uint64_t msSinceLastFrame, SDL_Surface* screen, Level* level);
};

} /* namespace game */

#endif /* PLASMABEAM_H_ */
