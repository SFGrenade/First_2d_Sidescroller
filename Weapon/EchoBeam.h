/*
 * EchoBeam.h
 *
 *  Created on: 11.02.2017
 *      Author: SFG
 */

#ifndef ECHOBEAM_H_
#define ECHOBEAM_H_

#include "Weapon.h"

namespace game {

class EchoBeam: public Weapon {
public:
	EchoBeam();
	virtual ~EchoBeam();

	void shoot(twoDPos from, twoDPos to);
	void compute(uint64_t msSinceLastFrame, SDL_Surface* screen, Level* level);
};

} /* namespace game */

#endif /* ECHOBEAM_H_ */
