/*
 * Tile.h
 *
 *  Created on: 27.01.2017
 *      Author: SFG
 */

#ifndef TILE_H_
#define TILE_H_

#include <stdint.h>
#include <string>

#include "../Weapon/Projectiles/BaseProjectile.h"


namespace game {

typedef enum terrainType {
  TERRAINTYPE_EMPTY,
  TERRAINTYPE_NORMAL,
  TERRAINTYPE_WATER,
  TERRAINTYPE_LADDER,
  TERRAINTYPE_DOOR_UP,
  TERRAINTYPE_DOOR_DOWN,
  TERRAINTYPE_DOOR_LEFT,
  TERRAINTYPE_DOOR_RIGHT,
  TERRAINTYPE_ONE_WAY_L_R,
  TERRAINTYPE_ONE_WAY_R_L,
  TERRAINTYPE_ONE_WAY_D_U,
  TERRAINTYPE_ONE_WAY_U_D,
  TERRAINTYPE_SLOPE_L_R_1x1,
  TERRAINTYPE_SLOPE_R_L_1x1,
  TERRAINTYPE_SLOPE_L_R_1x2_1,
  TERRAINTYPE_SLOPE_R_L_1x2_1,
  TERRAINTYPE_SLOPE_L_R_1x2_2,
  TERRAINTYPE_SLOPE_R_L_1x2_2,
  TERRAINTYPE_SLOPE_L_R_2x1_1,
  TERRAINTYPE_SLOPE_R_L_2x1_1,
  TERRAINTYPE_SLOPE_L_R_2x1_2,
  TERRAINTYPE_SLOPE_R_L_2x1_2
} terrainType;

class Player;
class BaseEntity;
class Map;

class Tile {
  protected:
  uint16_t mType;
  uint32_t mColor;
  terrainType mTerrainType;

  public:
  Tile( uint16_t tileType = 0, uint32_t tileColor = 0, int tileTerrainType = TERRAINTYPE_EMPTY );
  virtual ~Tile();

  virtual std::string toString();
  uint32_t getColor();
  uint16_t getType();
  terrainType getTerrainType();

  virtual void collide( Player* player, Map* map ) = 0;
  virtual void collideEntity( BaseEntity* entity, Map* map ) = 0;
  virtual void hit( DamageType damageType ) = 0;
};

} /* namespace game */

#endif /* TILE_H_ */
