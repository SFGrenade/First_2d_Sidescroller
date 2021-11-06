/*
 * Player.cpp
 *
 *  Created on: 28.01.2017
 *      Author: SFG
 */

#include "Player.h"
#include "../Level/Map.h"
#include "../Level/Level.h"
#include "../Level/Tile.h"
#include "../Level/EmptyTile.h"
#include "../Level/TransitionTile.h"
#include "../Level/WallTile.h"
#include "../Level/WaterTile.h"
#include "../Weapon/DebugWeapon.h"
#include "../Weapon/AnnihilatorBeam.h"
#include "../Weapon/EchoBeam.h"
#include "../Weapon/GrappleBeam.h"
#include "../Weapon/IceBeam.h"
#include "../Weapon/MolecularBeam.h"
#include "../Weapon/PowerBeam.h"
#include "../Weapon/PlasmaBeam.h"
#include "../Weapon/SniperBeam.h"
#include "../Weapon/WaveBeam.h"
#include <cmath>

namespace game {

Player::Player(double x, double y, uint16_t sizeX, uint16_t sizeY) :
		_position( { (double) (x * gridWidth), (double) (y * gridWidth), (uint16_t) sizeX, (uint16_t) sizeY }), up(false), down(false), left(false), right(false), colUp(false), colDown(true), colLeft(false), colRight(false), moveXSpeed(250.0), moveYSpeed(0.0), tilemap(NULL), level(NULL) {
	weapon.add(new PowerBeam());
	weapon.add(new AnnihilatorBeam());
	weapon.add(new EchoBeam());
	weapon.add(new GrappleBeam());
	weapon.add(new IceBeam());
	weapon.add(new MolecularBeam());
	weapon.add(new PlasmaBeam());
	weapon.add(new SniperBeam());
	weapon.add(new WaveBeam());
}

Player::~Player() {
	tilemap = NULL;

}

void Player::setPos(double x, double y) {
	_position = *(new OwnRect { x, y, _position.w, _position.h });
}

double Player::getXPos() {
	return _position.x;
}
double Player::getYPos() {
	return _position.y;
}
uint16_t Player::getW() {
	return _position.w;
}
uint16_t Player::getH() {
	return _position.h;
}

void Player::setTilemap(std::vector<std::vector<Tile*> >* tilemap, Level* level) {
	this->tilemap = tilemap;
	this->level = level;
}

void Player::setUp(bool isUp, double jumpForce) {
	up = isUp;
	if (isUp && colDown) {
		moveYSpeed -= jumpForce;
		colDown = false;
	} else if (!isUp && !colDown && (moveYSpeed < 0)) {
		moveYSpeed = 0;
	}
}
void Player::setDown(bool isDown) {
	down = isDown;
}
void Player::setLeft(bool isLeft) {
	left = isLeft;
}
void Player::setRight(bool isRight) {
	right = isRight;
}

bool contains(std::vector<Tile*> *collisionList, Tile *collision) {
	for (std::vector<Tile*>::iterator listItem = collisionList->begin(); listItem != collisionList->end(); listItem++) {
		if (collision == (*listItem)) {
			return true;
		}
	}
	return false;
}

void Player::updatePosition(uint64_t msSinceLastFrame, Map* map) {
	// First, the X axis
	double newXPos = _position.x;
	collisions.clear();
	if (left) {
		// Going left
		newXPos -= moveXSpeed * ((double) msSinceLastFrame / 1000.0);
		uint16_t xCollisions = 0;
		for (uint32_t i = 0; i < (uint16_t) _position.h; i++) {
			uint16_t yCheck = (_position.y + i) / gridWidth;
			if (tilemap->operator [](yCheck)[newXPos / gridWidth]->getType() != 0) {
				if (!contains(&collisions, tilemap->operator [](yCheck)[newXPos / gridWidth])) {
					collisions.push_back(tilemap->operator [](yCheck)[newXPos / gridWidth]);
					xCollisions++;
				}
			}
		}
		if (xCollisions) {
			// Collision left of the player found
			newXPos = ((int) _position.x / gridWidth) * gridWidth;
			colLeft = true;
		} else {
			colLeft = false;
		}
	}
	if (this->right) {
		// Going right
		newXPos += moveXSpeed * ((double) msSinceLastFrame / 1000.0);
		uint16_t xCollisions = 0;
		for (uint32_t i = 0; i < (uint16_t) _position.h; i++) {
			uint16_t yCheck = (_position.y + i) / gridWidth;
			if (tilemap->operator [](yCheck)[(newXPos + _position.w) / gridWidth]->getType() != 0) {
				if (!contains(&collisions, tilemap->operator [](yCheck)[(newXPos + _position.w) / gridWidth])) {
					collisions.push_back(tilemap->operator [](yCheck)[(newXPos + _position.w) / gridWidth]);
					xCollisions++;
				}
			}
		}
		if (xCollisions) {
			// Collision right of the player found
			newXPos = ((int) newXPos / gridWidth) * gridWidth + (gridWidth - (_position.w % gridWidth));
			colRight = true;
		} else {
			colRight = false;
		}
	}
	// End of X axis
	// Lastly, the Y axis
	moveYSpeed += gravity * ((double) msSinceLastFrame / 1000.0);
	if (fabs(moveYSpeed * ((double) msSinceLastFrame / 1000.0)) > (double) gridWidth * 0.99) {
		moveYSpeed = ((double) gridWidth * 0.99) / ((double) msSinceLastFrame / 1000.0);
	}
	double newYPos = _position.y + moveYSpeed * ((double) msSinceLastFrame / 1000.0);
	if (moveYSpeed > 0) {
		// Going down
		uint16_t yCollisions = 0;
		for (uint32_t i = 0; i < (uint16_t) _position.w; i++) {
			uint16_t xCheck = (_position.x + i) / gridWidth;
			if (tilemap->operator []((newYPos + _position.h) / gridWidth)[xCheck]->getType() != 0) {
				if (!contains(&collisions, tilemap->operator []((newYPos + _position.h) / gridWidth)[xCheck])) {
					collisions.push_back(tilemap->operator []((newYPos + _position.h) / gridWidth)[xCheck]);
					yCollisions++;
				}
			}
		}
		if (yCollisions) {
			// Collision under the player found
			newYPos = ((int) newYPos / gridWidth) * gridWidth + (gridWidth - (_position.h % gridWidth));
			moveYSpeed = 0;
			colDown = true;
		} else {
			colDown = false;
		}
	} else {
		// Going up
		uint16_t yCollisions = 0;
		for (uint32_t i = 0; i < (uint16_t) _position.w; i++) {
			uint16_t xCheck = (_position.x + i) / gridWidth;
			if (tilemap->operator [](newYPos / gridWidth)[xCheck]->getType() != 0) {
				if (!contains(&collisions, tilemap->operator [](newYPos / gridWidth)[xCheck])) {
					collisions.push_back(tilemap->operator [](newYPos / gridWidth)[xCheck]);
					yCollisions++;
				}
			}
		}
		if (yCollisions) {
			// Collision over the player found
			newYPos = ((int) _position.y / gridWidth) * gridWidth;
			moveYSpeed = 0;
			colUp = true;
		} else {
			colUp = false;
		}
	}
	// End of Y axis
	setPos(newXPos, newYPos);
	for (uint16_t i = 0; i < collisions.size(); i++) {
		collisions[i]->collide(this, map);
	}
}

void Player::rollWpnNext() {
	weapon.rollNext();
}
void Player::rollWpnPrev() {
	weapon.rollPrev();
}
Weapon* Player::getWeapon(int offset) {
	return weapon.getCurrentData(offset);
}

OwnRect* Player::getPosition() {
	return &_position;
}

void Player::onMouseButtonDown(SDL_MouseButtonEvent e) {
	twoDPos event = { (double) e.x + level->getViewRect()->x, (double) e.y + level->getViewRect()->y };
	twoDPos from = { _position.x + _position.w / 2, _position.y + _position.h / 2 };
	if (event.x != _position.x) {
		double dx = from.x - event.x;
		double dy = from.y - event.y;

		if (abs(dx) > abs(dy)) {
			if (dx > 0) {
				event.x = from.x - level->getW();
				event.y = from.y - ((dy / dx) * level->getW());
			} else {
				event.x = from.x + level->getW();
				event.y = from.y + ((dy / dx) * level->getW());
			}
		} else {
			if (dy > 0) {
				event.y = from.y - level->getH();
				event.x = from.x - ((dx / dy) * level->getH());
			} else {
				event.y = from.y + level->getH();
				event.x = from.x + ((dx / dy) * level->getH());
			}
		}
		weapon.getCurrentData(0)->shoot(twoDPos { from.x, from.y }, twoDPos { event.x, event.y });
	} else {
		weapon.getCurrentData(0)->shoot(twoDPos { from.x, from.y }, twoDPos { event.x, event.y });
	}
}
void Player::onMouseButtonUp(SDL_MouseButtonEvent e) {
}

std::vector<Weapon*> Player::getWeapons() {
	std::vector<Weapon*> ret;
	Weapon* first = weapon.getFirst()->getData();
	Weapon* current = weapon.getCurrentData(0);
	weapon.rollTo(0);
	while (weapon.getCurrentData(1) != first) {
		ret.push_back(weapon.getCurrentData(0));
		weapon.rollNext();
	}
	ret.push_back(weapon.getCurrentData(0));
	while (current != weapon.getCurrentData(0)) {
		weapon.rollNext();
	}
	return ret;
}

} /* namespace game */
