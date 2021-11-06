/*
 * IceBeam.cpp
 *
 *  Created on: 11.02.2017
 *      Author: SFG
 */

#include "IceBeam.h"
#include "Projectiles/BaseProjectile.h"
#include "Projectiles/IceBeamProjectile.h"
#include "../Level/Level.h"

namespace game {

IceBeam::IceBeam() : Weapon(".\\Img\\IceBeam.png", "Ice Beam", "The Ice Beam", "Maybe it\'s the Ice Beam") {
}

IceBeam::~IceBeam() {
	this->~Weapon();
}

void IceBeam::shoot(twoDPos from, twoDPos to) {
	this->projectiles.push_back(new IceBeamProjectile(from, to, 500));
}

void IceBeam::compute(uint64_t msSinceLastFrame, SDL_Surface* screen, Level* level) {
	uint16_t i = 0;
	for (BaseProjectile* value : projectiles) {
		if (value->alive() != true) {
			projectiles.erase(projectiles.begin() + i);
		} else {
			value->compute(msSinceLastFrame, screen, level);
			i++;
		}
	}
}

} /* namespace game */
