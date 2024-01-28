/*
 * BaseEntity.h
 *
 *  Created on: 25.03.2017
 *      Author: SFG
 */

#ifndef ENTITY_BASEENTITY_H_
#define ENTITY_BASEENTITY_H_

#include <stdint.h>
#include <vector>

#include "../overallObjects.h"


typedef struct {
  double x, y;
  uint16_t w, h;
} OwnRectEntity;

namespace game {

class Tile;
class Level;
class Map;
class Player;

class BaseEntity {
  protected:
  OwnRectEntity _position;
  bool up, down, left, right;
  bool colUp, colDown, colLeft, colRight;
  double moveXSpeed;
  double moveYSpeed;

  std::vector< std::vector< Tile* > >* tilemap;
  Level* level;
  std::vector< Tile* > collisions;

  public:
  BaseEntity( double x = 0, double y = 0, uint16_t sizeX = 1, uint16_t sizeY = 1 );
  virtual ~BaseEntity();
  double getXPos();
  double getYPos();
  uint16_t getW();
  uint16_t getH();

  void setTilemap( std::vector< std::vector< Tile* > >* tilemap, Level* level );

  virtual void setUp( bool isUp, double jumpForce = 0 );
  virtual void setDown( bool isDown );
  virtual void setLeft( bool isLeft );
  virtual void setRight( bool isRight );

  void setPos( double x, double y );

  virtual void update( Player* player );
  virtual void updatePosition( uint64_t msSinceLastFrame, Map* map );

  OwnRectEntity* getPosition();
};

} /* namespace game */

#endif /* ENTITY_BASEENTITY_H_ */
