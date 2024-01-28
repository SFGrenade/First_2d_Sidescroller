/*
 * EnemyEntity.h
 *
 *  Created on: 07.04.2017
 *      Author: SFG
 */

#ifndef ENTITY_ENEMYENTITY_H_
#define ENTITY_ENEMYENTITY_H_

#include <stdint.h>
#include <vector>

#include "../overallObjects.h"
#include "BaseEntity.h"


namespace game {

class Player;

class EnemyEntity : public BaseEntity {
  protected:
  int16_t _maxHealth, _currentHealth;

  bool _moveVertical;
  uint16_t _moveRadius;

  public:
  EnemyEntity( double x = 0,
               double y = 0,
               uint16_t sizeX = 1,
               uint16_t sizeY = 1,
               int16_t maxHealth = 1,
               bool verticalMovement = false,
               uint16_t moveRadius = 0 );
  virtual ~EnemyEntity();

  virtual void setUp( bool isUp, double jumpForce = ( 0.3175 * gravity * ( gridWidth / 32.0 ) ) );
  virtual void setDown( bool isDown );
  virtual void setLeft( bool isLeft );
  virtual void setRight( bool isRight );

  virtual void update( Player* player );
  virtual void updatePosition( uint64_t msSinceLastFrame, Map* map );
};

} /* namespace game */

#endif /* ENTITY_ENEMYENTITY_H_ */
