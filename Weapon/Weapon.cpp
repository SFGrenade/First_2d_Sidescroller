/*
 * Weapon.cpp
 *
 *  Created on: 03.02.2017
 *      Author: SFG
 */

#include "Weapon.h"

namespace game {

Weapon::Weapon(const char* pathToFile, const char* name, const char* shortDesc, const char* longDesc) : name((char*) name), shortDesc((char*) shortDesc), longDesc((char*) longDesc) {
	image = IMG_Load(pathToFile);
	image = SDL_ConvertSurfaceFormat(image, SDL_PIXELFORMAT_RGBA32, 0);
}

Weapon::~Weapon() {
	SDL_FreeSurface(image);
	image = NULL;
	name = NULL;
	shortDesc = NULL;
	longDesc = NULL;
}

SDL_Surface* Weapon::getImage() {
	return image;
}

char* Weapon::getName() {
	return name;
}

char* Weapon::getShortDesc() {
	return shortDesc;
}

char* Weapon::getLongDesc() {
	return longDesc;
}

} /* namespace game */
