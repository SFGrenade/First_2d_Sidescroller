/*
 * BaseProjectile.h
 *
 *  Created on: 11.02.2017
 *      Author: SFG
 */

#ifndef BASEPROJECTILE_H_
#define BASEPROJECTILE_H_

#include <list>
#include "../../overallObjects.h"

namespace game {

typedef enum damageType {
	DAMAGETYPE_POWERBEAM,
	DAMAGETYPE_ANNIHILATORBEAM,
	DAMAGETYPE_ECHOBEAM,
	DAMAGETYPE_GRAPPLEBEAM,
	DAMAGETYPE_ICEBEAM,
	DAMAGETYPE_MOLECULARBEAM,
	DAMAGETYPE_PLASMABEAM,
	DAMAGETYPE_SNIPERBEAM,
	DAMAGETYPE_WAVEBEAM
} DamageType;

class Level;

class BaseProjectile {
protected:
	twoDPos _from, _to;
	int64_t _timeToLive;
	bool _computed;
public:
	BaseProjectile(twoDPos from, twoDPos to, int64_t timeToLive);
	virtual ~BaseProjectile();

	bool alive();
	virtual std::list<twoDPos> line(twoDPos from, twoDPos to, SDL_Surface* screen);

	virtual void compute(uint64_t msSinceLastFrame, SDL_Surface* screen, Level* level) = 0;
};

} /* namespace game */

#endif /* BASEPROJECTILE_H_ */
