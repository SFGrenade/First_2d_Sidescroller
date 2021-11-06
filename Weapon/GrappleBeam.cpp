/*
 * GrappleBeam.cpp
 *
 *  Created on: 11.02.2017
 *      Author: SFG
 */

#include "GrappleBeam.h"
#include "Projectiles/BaseProjectile.h"
#include "Projectiles/GrappleBeamProjectile.h"
#include "../Level/Level.h"

namespace game {

GrappleBeam::GrappleBeam() : Weapon(".\\Img\\GrappleBeam.png", "Grapple Beam", "The Grapple Beam", "Maybe it\'s the Grapple Beam") {
}

GrappleBeam::~GrappleBeam() {
	this->~Weapon();
}

void GrappleBeam::shoot(twoDPos from, twoDPos to) {
	this->projectiles.push_back(new GrappleBeamProjectile(from, to, 500));
}

void GrappleBeam::compute(uint64_t msSinceLastFrame, SDL_Surface* screen, Level* level) {
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
