/*
 * BaseProjectile.cpp
 *
 *  Created on: 11.02.2017
 *      Author: SFG
 */

#include "BaseProjectile.h"

#include <cstdlib>
#include <iostream>


namespace game {

BaseProjectile::BaseProjectile( twoDPos from, twoDPos to, int64_t timeToLive ) : _from( from ), _to( to ), _timeToLive( timeToLive ), _computed( false ) {}

BaseProjectile::~BaseProjectile() {}

bool BaseProjectile::alive() {
  return ( 0 < _timeToLive );
}

std::list< twoDPos > BaseProjectile::line( twoDPos from, twoDPos to, SDL_Surface* screen ) {
  from.x = (double)(int)from.x;
  from.y = (double)(int)from.y;
  to.x = (double)(int)to.x;
  to.y = (double)(int)to.y;

  int delta_x( to.x - from.x );
  // if from.x == to.x, then it does not matter what we set here
  signed char const ix( ( delta_x > 0 ) - ( delta_x < 0 ) );
  delta_x = std::abs( delta_x ) << 1;

  int delta_y( to.y - from.y );
  // if from.y == to.y, then it does not matter what we set here
  signed char const iy( ( delta_y > 0 ) - ( delta_y < 0 ) );
  delta_y = std::abs( delta_y ) << 1;

  std::list< twoDPos > ret;
  ret.push_back( from );

  if( delta_x >= delta_y ) {
    // error may go below zero
    int error( delta_y - ( delta_x >> 1 ) );

    while( from.x != to.x ) {
      if( ( error >= 0 ) && ( error || ( ix > 0 ) ) ) {
        error -= delta_x;
        from.y += iy;
      }
      // else do nothing

      error += delta_y;
      from.x += ix;

      if( 0 <= from.x && from.x < screen->w && 0 <= from.y && from.y < screen->h ) {
        ret.push_back( from );
      }
    }
  } else {
    // error may go below zero
    int error( delta_x - ( delta_y >> 1 ) );

    while( from.y != to.y ) {
      if( ( error >= 0 ) && ( error || ( iy > 0 ) ) ) {
        error -= delta_y;
        from.x += ix;
      }
      // else do nothing

      error += delta_x;
      from.y += iy;

      if( 0 <= from.x && from.x < screen->w && 0 <= from.y && from.y < screen->h ) {
        ret.push_back( from );
      }
    }
  }
  return ret;
}

} /* namespace game */
