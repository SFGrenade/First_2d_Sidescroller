/*
 * WaterTile.h
 *
 *  Created on: 10.02.2017
 *      Author: SFG
 */

#ifndef WATERTILE_H_
#define WATERTILE_H_

#include "Tile.h"

namespace game {

class WaterTile : public Tile {
  public:
  WaterTile( uint16_t tileType = 0, uint32_t tileColor = 0, int tileTerrainType = TERRAINTYPE_WATER );
  virtual ~WaterTile();

  virtual std::string toString();

  void collide( Player* player, Map* map );
  void collideEntity( BaseEntity* entity, Map* map );
  void hit( DamageType damageType );
};

} /* namespace game */

#endif /* WATERTILE_H_ */
