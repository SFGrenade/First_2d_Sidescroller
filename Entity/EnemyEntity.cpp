/*
 * EnemyEntity.cpp
 *
 *  Created on: 07.04.2017
 *      Author: SFG
 */

#include "EnemyEntity.h"

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

EnemyEntity::EnemyEntity( double x, double y, uint16_t sizeX, uint16_t sizeY, int16_t maxHealth, bool verticalMovement, uint16_t moveRadius )
    : BaseEntity( x, y, sizeX, sizeY ), _maxHealth( maxHealth ), _currentHealth( _maxHealth ), _moveVertical( verticalMovement ), _moveRadius( moveRadius ) {}

EnemyEntity::~EnemyEntity() {
  // this->~BaseEntity();
}

void EnemyEntity::setUp( bool isUp, double jumpForce ) {
  up = isUp;
  if( isUp && colDown ) {
    moveYSpeed -= jumpForce;
    colDown = false;
  } else if( !isUp && !colDown && ( moveYSpeed < 0 ) ) {
    moveYSpeed = 0;
  }
}
void EnemyEntity::setDown( bool isDown ) {
  down = isDown;
}
void EnemyEntity::setLeft( bool isLeft ) {
  left = isLeft;
}
void EnemyEntity::setRight( bool isRight ) {
  right = isRight;
}

void EnemyEntity::update( Player* player ) {
  if( _position.x > player->getXPos() ) {
    this->setLeft( true );
    this->setRight( false );
  } else if( _position.x < player->getXPos() ) {
    this->setLeft( false );
    this->setRight( true );
  } else {
    this->setLeft( false );
    this->setRight( false );
  }

  if( _position.y > player->getYPos() ) {
    this->setUp( true );
    this->setDown( false );
  } else if( _position.y < player->getYPos() ) {
    this->setUp( false );
    this->setDown( true );
  } else {
    this->setUp( false );
    this->setDown( false );
  }
}
void EnemyEntity::updatePosition( uint64_t msSinceLastFrame, Map* map ) {
  // First, the X axis
  double newXPos = _position.x;
  collisions.clear();
  if( left ) {
    // Going left
    newXPos -= moveXSpeed * ( (double)msSinceLastFrame / 1000.0 );
    uint16_t xCollisions = 0;
    for( uint32_t i = 0; i < ( uint16_t )( _position.h / gridWidth ); i++ ) {
      uint16_t yCheck = ( _position.y + ( gridWidth * i ) - ( 0 > i ) ) / gridWidth;
      if( tilemap->operator[]( yCheck )[newXPos / gridWidth]->getType() != 0 ) {
        collisions.push_back( tilemap->operator[]( yCheck )[newXPos / gridWidth] );
        xCollisions++;
      }
    }
    if( tilemap->operator[]( ( _position.y + _position.h - 1 ) / gridWidth )[newXPos / gridWidth]->getType() != 0 ) {
      collisions.push_back( tilemap->operator[]( ( _position.y + _position.h - 1 ) / gridWidth )[newXPos / gridWidth] );
      xCollisions++;
    }
    if( xCollisions ) {
      // Collision left of the player found
      newXPos = ( ( (int)_position.x + 0 ) / gridWidth ) * gridWidth;
      colLeft = true;
    } else {
      colLeft = false;
    }
  }
  if( this->right ) {
    // Going right
    newXPos += moveXSpeed * ( (double)msSinceLastFrame / 1000.0 );
    uint16_t xCollisions = 0;
    for( uint32_t i = 0; i < ( uint16_t )( _position.h / gridWidth ); i++ ) {
      uint16_t yCheck = ( _position.y + ( gridWidth * i ) - ( 0 > i ) ) / gridWidth;
      if( tilemap->operator[]( yCheck )[( newXPos / gridWidth ) + ( _position.w / gridWidth )]->getType() != 0 ) {
        collisions.push_back( tilemap->operator[]( yCheck )[( newXPos / gridWidth ) + ( _position.w / gridWidth )] );
        xCollisions++;
      }
    }
    if( tilemap->operator[]( ( _position.y + _position.h - 1 ) / gridWidth )[( newXPos / gridWidth ) + ( _position.w / gridWidth )]->getType() != 0 ) {
      collisions.push_back( tilemap->operator[]( ( _position.y + _position.h - 1 ) / gridWidth )[( newXPos / gridWidth ) + ( _position.w / gridWidth )] );
      xCollisions++;
    }
    if( xCollisions ) {
      // Collision right of the player found
      newXPos = _position.x + moveXSpeed * ( (double)msSinceLastFrame / 1000.0 );
      newXPos = ( ( (int)newXPos + 1 ) / gridWidth ) * gridWidth;
      colRight = true;
    } else {
      colRight = false;
    }
  }
  // End of X axis
  // Lastly, the Y axis
  moveYSpeed += gravity * ( (double)msSinceLastFrame / 1000.0 );
  if( fabs( moveYSpeed * ( (double)msSinceLastFrame / 1000.0 ) ) > (double)gridWidth * 0.99 ) {
    moveYSpeed = ( (double)gridWidth * 0.99 ) / ( (double)msSinceLastFrame / 1000.0 );
  }
  double newYPos = _position.y + moveYSpeed * ( (double)msSinceLastFrame / 1000.0 );
  if( moveYSpeed > 0 ) {
    // Going down
    uint16_t yCollisions = 0;
    for( uint32_t i = 0; i < ( uint16_t )( _position.w / gridWidth ); i++ ) {
      uint16_t xCheck = ( _position.x + ( gridWidth * i ) - ( 0 > i ) ) / gridWidth;
      if( tilemap->operator[]( ( newYPos / gridWidth ) + ( _position.h / gridWidth ) )[xCheck]->getType() != 0 ) {
        collisions.push_back( tilemap->operator[]( ( newYPos / gridWidth ) + ( _position.h / gridWidth ) )[xCheck] );
        yCollisions++;
      }
    }
    if( tilemap->operator[]( ( newYPos / gridWidth ) + ( _position.h / gridWidth ) )[( _position.x + _position.w - 1 ) / gridWidth]->getType() != 0 ) {
      collisions.push_back( tilemap->operator[]( ( newYPos / gridWidth ) + ( _position.h / gridWidth ) )[( _position.x + _position.w - 1 ) / gridWidth] );
      yCollisions++;
    }

    if( yCollisions ) {
      // Collision under the player found
      newYPos = _position.y + moveYSpeed * ( (double)msSinceLastFrame / 1000.0 );
      newYPos = ( ( (int)newYPos + 1 ) / gridWidth ) * gridWidth;
      moveYSpeed = 0;
      colDown = true;
    } else {
      colDown = false;
    }
  } else {
    // Going up
    uint16_t yCollisions = 0;
    for( uint32_t i = 0; i < ( uint16_t )( _position.w / 32 ); i++ ) {
      uint16_t xCheck = ( _position.x + ( gridWidth * i ) - ( 0 > i ) ) / gridWidth;
      if( tilemap->operator[]( newYPos / gridWidth )[xCheck]->getType() != 0 ) {
        collisions.push_back( tilemap->operator[]( newYPos / gridWidth )[xCheck] );
        yCollisions++;
      }
    }
    if( tilemap->operator[]( newYPos / gridWidth )[( _position.x + _position.w - 1 ) / gridWidth]->getType() != 0 ) {
      collisions.push_back( tilemap->operator[]( newYPos / gridWidth )[( _position.x + _position.w - 1 ) / gridWidth] );
      yCollisions++;
    }

    if( yCollisions ) {
      // Collision over the player found
      newYPos = ( ( (int)_position.y + 0 ) / gridWidth ) * gridWidth;
      moveYSpeed = 0;
      colUp = true;
    } else {
      colUp = false;
    }
  }
  // End of Y axis
  setPos( newXPos, newYPos );
  for( uint16_t i = 0; i < collisions.size(); i++ ) {
    collisions[i]->collideEntity( this, map );
  }
}

} /* namespace game */
