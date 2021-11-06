/*
 * EmptyTile.h
 *
 *  Created on: 10.02.2017
 *      Author: SFG
 */

#ifndef EMPTYTILE_H_
#define EMPTYTILE_H_

#include "Tile.h"

namespace game {

class EmptyTile: public Tile {
public:
	EmptyTile();
	virtual ~EmptyTile();

	virtual std::string toString();

	void collide(Player* player, Map* map);
	void collideEntity(BaseEntity* entity, Map* map);
	void hit(DamageType damageType);
};

} /* namespace game */

#endif /* EMPTYTILE_H_ */
