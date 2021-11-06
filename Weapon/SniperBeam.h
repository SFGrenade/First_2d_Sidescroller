/*
 * SniperBeam.h
 *
 *  Created on: 11.02.2017
 *      Author: SFG
 */

#ifndef SNIPERBEAM_H_
#define SNIPERBEAM_H_

#include "Weapon.h"

namespace game {

class SniperBeam: public Weapon {
public:
	SniperBeam();
	virtual ~SniperBeam();

	void shoot(twoDPos from, twoDPos to);
	void compute(uint64_t msSinceLastFrame, SDL_Surface* screen, Level* level);
};

} /* namespace game */

#endif /* SNIPERBEAM_H_ */
