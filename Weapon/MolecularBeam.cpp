/*
 * MolecularBeam.cpp
 *
 *  Created on: 11.02.2017
 *      Author: SFG
 */

#include "MolecularBeam.h"
#include "Projectiles/BaseProjectile.h"
#include "Projectiles/MolecularBeamProjectile.h"
#include "../Level/Level.h"

namespace game {

MolecularBeam::MolecularBeam() : Weapon(".\\Img\\MolecularBeam.png", "Molecular Beam", "The Molecular Beam", "Maybe it\'s the Molecular Beam") {
}

MolecularBeam::~MolecularBeam() {
	this->~Weapon();
}

void MolecularBeam::shoot(twoDPos from, twoDPos to) {
	this->projectiles.push_back(new MolecularBeamProjectile(from, to, 500));
}

void MolecularBeam::compute(uint64_t msSinceLastFrame, SDL_Surface* screen, Level* level) {
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
