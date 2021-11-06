/*
 * PowerBeam.cpp
 *
 *  Created on: 11.02.2017
 *      Author: SFG
 */

#include "PowerBeam.h"
#include "Projectiles/BaseProjectile.h"
#include "Projectiles/PowerBeamProjectile.h"
#include "../Level/Level.h"

namespace game {

PowerBeam::PowerBeam() : Weapon(".\\Img\\PowerBeam.png", "Power Beam", "The Power Beam", "Maybe it\'s the Power Beam") {
}

PowerBeam::~PowerBeam() {
	this->~Weapon();
}

void PowerBeam::shoot(twoDPos from, twoDPos to) {
	this->projectiles.push_back(new PowerBeamProjectile(from, to, 500));
}

void PowerBeam::compute(uint64_t msSinceLastFrame, SDL_Surface* screen, Level* level) {
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
