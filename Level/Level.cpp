/*
 * Level.cpp
 *
 *  Created on: 27.01.2017
 *      Author: SFG
 */

#include "Level.h"

#include <iostream>

#include "../Entity/BaseEntity.h"
#include "../Player/Player.h"
#include "EmptyTile.h"
#include "Tile.h"


namespace game {

Level::Level( uint16_t w, uint16_t h ) : mPlayer( NULL ), oldPlayerPos( new SDL_Rect{ 0, 0, 0, 0 } ), drawn( false ) {
  for( uint16_t row = 0; row < h; row++ ) {
    tilemap.push_back( std::vector< Tile* >() );
    for( uint16_t cell = 0; cell < w; cell++ ) {
      tilemap[row].push_back( (Tile*)new EmptyTile() );
    }
  }
  if( tilemap.size() > 0 ) {
    levelSurface = SDL_CreateRGBSurface( 0, gridWidth * tilemap[0].size(), gridWidth * tilemap.size(), 32, 0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF );
    finalSurface = SDL_CreateRGBSurface( 0, gridWidth * tilemap[0].size(), gridWidth * tilemap.size(), 32, 0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF );
  } else {
    levelSurface = SDL_CreateRGBSurface( 0, 0, 0, 32, 0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF );
    finalSurface = SDL_CreateRGBSurface( 0, 0, 0, 32, 0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF );
  }
  viewRect = new SDL_Rect{ 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
}

Level::~Level() {
  SDL_FreeSurface( levelSurface );
  // delete levelSurface;
  delete viewRect;
  mPlayer = NULL;
}

std::string Level::toString() {
  std::string ret( "" );
  for( uint16_t row = 0; row < tilemap.size(); row++ ) {
    for( uint16_t cell = 0; cell < tilemap[0].size(); cell++ ) {
      ret.append( tilemap[row][cell]->toString() );
      ret.append( ", " );
    }
    ret.append( "\n" );
  }
  return ret;
}

Tile* Level::getTile( uint16_t x, uint16_t y ) {
  return tilemap[y][x];
}
void Level::setTile( uint16_t x, uint16_t y, Tile* tile ) {
  if( !( x >= tilemap[y].size() || y >= tilemap.size() ) ) {
    if( tilemap[y][x] ) {
      delete tilemap[y][x];
    }
    tilemap[y][x] = (Tile*)tile;
  }
}

void Level::setOuterBorder( Tile* tile ) {
  for( uint16_t row = 0; row < tilemap.size(); row++ ) {
    for( uint16_t cell = 0; cell < tilemap[0].size(); cell++ ) {
      if( row == 0 || row == tilemap.size() - 1 ) {
        setTile( cell, row, tile );
      }
    }
    if( !( row == 0 || row == tilemap.size() - 1 ) ) {
      setTile( 0, row, tile );
      setTile( tilemap[0].size() - 1, row, tile );
    }
  }
}

void Level::fillRect( uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, Tile* tile ) {
  for( uint16_t row = y1; row < y2 + 1; row++ ) {
    for( uint16_t cell = x1; cell < x2 + 1; cell++ ) {
      setTile( cell, row, tile );
    }
  }
}

void Level::setPlayer( game::Player* player ) {
  if( mPlayer != player ) {
    mPlayer = player;
    mPlayer->setTilemap( &tilemap, this );
  }
}

SDL_Surface* Level::getSurface() {
  if( !drawn ) {
    SDL_FillRect( levelSurface, NULL, 0x000000FF );
    SDL_Rect tmpBlock = { 0, 0, gridWidth, gridWidth };
    for( uint16_t row = 0; row < tilemap.size(); row++ ) {
      for( uint16_t cell = 0; cell < tilemap[0].size(); cell++ ) {
        tmpBlock.x = cell * gridWidth;
        tmpBlock.y = row * gridWidth;
        SDL_FillRect( levelSurface, &tmpBlock, tilemap[row][cell]->getColor() );
      }
    }
    drawn = true;
  }
  SDL_FillRect( finalSurface, viewRect, 0x000000FF );
  SDL_BlitSurface( levelSurface, viewRect, finalSurface, viewRect );

  SDL_Rect tmp = { 0, 0, gridWidth, gridWidth };

  for( uint16_t i = 0; i < entities.size(); i++ ) {
    tmp.x = entities[i]->getXPos();
    tmp.y = entities[i]->getYPos();
    tmp.w = entities[i]->getW();
    tmp.h = entities[i]->getH();
    SDL_FillRect( finalSurface, &tmp, 0xFF0080FF );
  }

  tmp.x = mPlayer->getPosition()->x;
  tmp.y = mPlayer->getPosition()->y;
  tmp.w = mPlayer->getPosition()->w;
  tmp.h = mPlayer->getPosition()->h;
  SDL_FillRect( finalSurface, &tmp, 0x00FF00FF );
  return finalSurface;
}

SDL_Rect* Level::getViewRect() {
  viewRect->x = ( (int)mPlayer->getXPos() ) + ( mPlayer->getW() / 2 ) - ( SCREEN_WIDTH / 2 );
  if( viewRect->x < 0 ) {
    viewRect->x = 0;
  } else if( (int32_t)viewRect->x > ( int32_t )( tilemap[0].size() * gridWidth ) - viewRect->w ) {
    viewRect->x = ( tilemap[0].size() * gridWidth ) - viewRect->w;
  }
  viewRect->y = ( (int)mPlayer->getYPos() ) + ( mPlayer->getH() / 2 ) - ( SCREEN_HEIGHT / 2 );
  if( viewRect->y < 0 ) {
    viewRect->y = 0;
  } else if( (int32_t)viewRect->y > ( int32_t )( tilemap.size() * gridWidth ) - viewRect->h ) {
    viewRect->y = ( tilemap.size() * gridWidth ) - viewRect->h;
  }
  return viewRect;
}

uint32_t Level::getW() {
  return levelSurface->w;
}
uint32_t Level::getH() {
  return levelSurface->h;
}

void Level::addEntity( BaseEntity* newEntity ) {
  newEntity->setTilemap( &tilemap, this );
  entities.push_back( newEntity );
}
void Level::updateEntities() {
  for( uint16_t i = 0; i < entities.size(); i++ ) {
    entities[i]->update( mPlayer );
  }
}
std::vector< BaseEntity* > Level::getEntities() {
  return entities;
}

} /* namespace game */
