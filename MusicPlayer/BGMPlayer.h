/*
 * BGMPlayer.h
 *
 *  Created on: 05.03.2017
 *      Author: SFG
 */

#ifndef BGMPLAYER_H_
#define BGMPLAYER_H_

#include <SDL2/SDL_mixer.h>
#include "../overallObjects.h"

namespace game {

class BGMPlayer {
protected:
	Mix_Music* bgm;
public:
	BGMPlayer();
	virtual ~BGMPlayer();

	void play();

	void loadBGM(const char* bgmName);
};

} /* namespace game */

#endif /* BGMPLAYER_H_ */
