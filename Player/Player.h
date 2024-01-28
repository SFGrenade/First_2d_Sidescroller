/*
 * Player.h
 *
 *  Created on: 28.01.2017
 *      Author: SFG
 */

#ifndef PLAYER_H_
#define PLAYER_H_

#include <stdint.h>
#include <vector>

#include "../RevolverList/RevolverList.h"
#include "../Weapon/Weapon.h"
#include "../overallObjects.h"


typedef struct {
  double x, y;
  uint16_t w, h;
} OwnRect;

namespace game {

class Tile;
class Level;
class Map;

class Player {
  private:
  OwnRect _position;
  bool up, down, left, right;
  bool colUp, colDown, colLeft, colRight;
  double moveXSpeed;
  double moveYSpeed;

  std::vector< std::vector< Tile* > >* tilemap;
  Level* level;
  std::vector< Tile* > collisions;

  RevolverList< Weapon* > weapon;

  public:
  Player( double x = 0, double y = 0, uint16_t sizeX = 1, uint16_t sizeY = 1 );
  virtual ~Player();
  double getXPos();
  double getYPos();
  uint16_t getW();
  uint16_t getH();

  void setTilemap( std::vector< std::vector< Tile* > >* tilemap, Level* level );

  void setUp( bool isUp, double jumpForce = ( 0.35 * gravity * ( gridWidth / 32.0 ) ) );
  void setDown( bool isDown );
  void setLeft( bool isLeft );
  void setRight( bool isRight );

  void setPos( double x, double y );

  void updatePosition( uint64_t msSinceLastFrame, Map* map );

  void rollWpnNext();
  void rollWpnPrev();
  Weapon* getWeapon( int offset = 0 );

  OwnRect* getPosition();

  void onMouseButtonDown( SDL_MouseButtonEvent e );
  void onMouseButtonUp( SDL_MouseButtonEvent e );

  std::vector< Weapon* > getWeapons();
};

} /* namespace game */

#endif /* PLAYER_H_ */
