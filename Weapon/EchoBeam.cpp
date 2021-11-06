/*
 * EchoBeam.cpp
 *
 *  Created on: 11.02.2017
 *      Author: SFG
 */

#include "EchoBeam.h"
#include "Projectiles/BaseProjectile.h"
#include "Projectiles/EchoBeamProjectile.h"
#include "../Level/Level.h"

namespace game {

EchoBeam::EchoBeam() : Weapon(".\\Img\\EchoBeam.png", "Echo Beam", "The Echo Beam", "Maybe it\'s the Echo Beam") {
}

EchoBeam::~EchoBeam() {
	this->~Weapon();
}

void EchoBeam::shoot(twoDPos from, twoDPos to) {
	this->projectiles.push_back(new EchoBeamProjectile(from, to, 500));
}

void EchoBeam::compute(uint64_t msSinceLastFrame, SDL_Surface* screen, Level* level) {
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
