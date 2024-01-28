/*
 * BaseEntity.cpp
 *
 *  Created on: 25.03.2017
 *      Author: SFG
 */

#include "BaseEntity.h"

#include <cmath>

#include "../Level/EmptyTile.h"
#include "../Level/Level.h"
#include "../Level/Map.h"
#include "../Level/Tile.h"
#include "../Level/TransitionTile.h"
#include "../Level/WallTile.h"
#include "../Level/WaterTile.h"
#include "../Player/Player.h"


namespace game {

BaseEntity::BaseEntity( double x, double y, uint16_t sizeX, uint16_t sizeY )
    : _position( { (double)( x * gridWidth ), (double)( y * gridWidth ), ( uint16_t )( sizeX * gridWidth ), ( uint16_t )( sizeY * gridWidth ) } ),
      up( false ),
      down( false ),
      left( false ),
      right( false ),
      colUp( false ),
      colDown( true ),
      colLeft( false ),
      colRight( false ),
      moveXSpeed( 100.0 ),
      moveYSpeed( 0.0 ),
      tilemap( NULL ),
      level( NULL ) {}

BaseEntity::~BaseEntity() {
  tilemap = NULL;
}

void BaseEntity::setPos( double x, double y ) {
  _position.x = x;
  _position.y = y;
}

double BaseEntity::getXPos() {
  return _position.x;
}
double BaseEntity::getYPos() {
  return _position.y;
}
uint16_t BaseEntity::getW() {
  return _position.w;
}
uint16_t BaseEntity::getH() {
  return _position.h;
}

void BaseEntity::setTilemap( std::vector< std::vector< Tile* > >* tilemap, Level* level ) {
  this->tilemap = tilemap;
  this->level = level;
}

void BaseEntity::setUp( bool isUp, double jumpForce ) {
  up = isUp;
}
void BaseEntity::setDown( bool isDown ) {
  down = isDown;
}
void BaseEntity::setLeft( bool isLeft ) {
  left = isLeft;
}
void BaseEntity::setRight( bool isRight ) {
  right = isRight;
}

void BaseEntity::update( Player* player ) {}
void BaseEntity::updatePosition( uint64_t msSinceLastFrame, Map* map ) {}

OwnRectEntity* BaseEntity::getPosition() {
  return &_position;
}

} /* namespace game */
