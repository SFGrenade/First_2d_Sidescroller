/*
 * Map.h
 *
 *  Created on: 25.02.2017
 *      Author: SFG
 */

#ifndef MAP_H_
#define MAP_H_

#include <vector>
#include <stdint.h>

namespace game {

class Level;
class BGMPlayer;

class Map {
	std::vector<Level*> levelVector;
	Level* selectedLevel;
	BGMPlayer* bgmPlayer;
	int currentIndex;
public:
	Map(BGMPlayer* newBgmPlayer);
	virtual ~Map();

	void addLevel(Level* level);
	void selectLevel(int index);
	Level* getSelectedLevel();

	Level* loadLevelXML(uint16_t levelNum, BGMPlayer* bgmPlayer);
	Level* loadLevelNew(uint16_t levelNum, BGMPlayer* bgmPlayer);

	void updateEntities(uint64_t msSinceLastFrame);
};

} /* namespace game */

#endif /* MAP_H_ */
