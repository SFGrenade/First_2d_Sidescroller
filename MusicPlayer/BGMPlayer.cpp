/*
 * BGMPlayer.cpp
 *
 *  Created on: 05.03.2017
 *      Author: SFG
 */

#include "BGMPlayer.h"

#include <string>


namespace game {

BGMPlayer::BGMPlayer() : bgm( NULL ) {
  Mix_VolumeMusic( 64 );
}

BGMPlayer::~BGMPlayer() {
  Mix_FreeMusic( bgm );
  bgm = NULL;
}

void BGMPlayer::play() {
  Mix_PlayMusic( bgm, -1 );
}

void BGMPlayer::loadBGM( const char* bgmName ) {
  Mix_HaltMusic();
  bgm = Mix_LoadMUS( ( std::string( ".\\Audio\\" ) + std::string( bgmName ) ).c_str() );
  this->play();
}

} /* namespace game */
