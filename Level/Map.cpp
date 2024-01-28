/*
 * Map.cpp
 *
 *  Created on: 25.02.2017
 *      Author: SFG
 */

#include "Map.h"

#include <iostream>
#include <string.h>
#include <string>

#include "../Entity/BaseEntity.h"
#include "../Entity/EnemyEntity.h"
#include "../MusicPlayer/BGMPlayer.h"
#include "../pugiXML/pugixml.hpp"
#include "Level.h"
#include "Tile.h"
#include "TransitionTile.h"
#include "WallTile.h"
#include "WaterTile.h"


namespace game {

Map::Map( BGMPlayer* newBgmPlayer ) : selectedLevel( NULL ), bgmPlayer( newBgmPlayer ), currentIndex( -1 ) {}

Map::~Map() {
  selectedLevel = NULL;
}

void Map::addLevel( Level* level ) {
  levelVector.push_back( level );
}

void Map::selectLevel( int index ) {
  if( index != currentIndex ) {
    Level* tmp = loadLevelNew( index + 1, bgmPlayer );
    if( tmp ) {
      if( selectedLevel ) {
        delete selectedLevel;
      }
      selectedLevel = tmp;
    }
    currentIndex = index;
  }
}

Level* Map::getSelectedLevel() {
  return selectedLevel;
}

Level* Map::loadLevelXML( uint16_t levelNum, BGMPlayer* bgmPlayer ) {
  pugi::xml_document doc;

  std::string file( ".\\Maps\\Level" );
  for( uint16_t i = 0; i < 3 - std::to_string( levelNum ).size(); i++ ) {
    file += std::string( "0" );
  }
  file += std::to_string( levelNum ) + std::string( ".xml" );
  pugi::xml_parse_result result = doc.load_file( file.c_str() );

  if( result.status == pugi::status_ok ) {
    uint16_t x = 0;
    uint16_t y = (uint16_t)doc.first_child().attribute( "height" ).as_uint() - 1;

    bgmPlayer->loadBGM( doc.first_child().attribute( "bgm" ).as_string() );

    game::Level* tmpLevel = new game::Level( doc.first_child().attribute( "width" ).as_uint(), y + 1 );

    doc.first_child().remove_child( "Entities" );
    for( pugi::xml_node::iterator rowIter = doc.first_child().begin(); rowIter != doc.first_child().end(); rowIter++ ) {
      x = 0;
      for( pugi::xml_node::iterator tileIter = ( *rowIter ).begin(); tileIter != ( *rowIter ).end(); tileIter++ ) {
        if( !strcmp( ( *tileIter ).name(), "EmptyTile" ) ) {
        } else if( !strcmp( ( *tileIter ).name(), "WallTile" ) ) {
          tmpLevel->setTile( x,
                             y,
                             new game::WallTile( ( *tileIter ).attribute( "tileType" ).as_uint(),
                                                 ( *tileIter ).attribute( "tileColor" ).as_uint(),
                                                 ( *tileIter ).attribute( "tileTerrainType" ).as_int() ) );
        } else if( !strcmp( ( *tileIter ).name(), "WaterTile" ) ) {
          tmpLevel->setTile( x, y, new game::WaterTile( ( *tileIter ).attribute( "tileType" ).as_uint(), ( *tileIter ).attribute( "tileColor" ).as_uint() ) );
        } else if( !strcmp( ( *tileIter ).name(), "TransitionTile" ) ) {
          tmpLevel->setTile( x,
                             y,
                             new game::TransitionTile( ( *tileIter ).attribute( "xTo" ).as_uint(),
                                                       ( *tileIter ).attribute( "yTo" ).as_uint(),
                                                       ( *tileIter ).attribute( "levelIndexTo" ).as_uint(),
                                                       ( *tileIter ).attribute( "tileType" ).as_uint(),
                                                       ( *tileIter ).attribute( "tileColor" ).as_uint() ) );
        }
        x++;
      }
      y--;
    }

    return tmpLevel;
  }
  return NULL;
}

Level* Map::loadLevelNew( uint16_t levelNum, BGMPlayer* bgmPlayer ) {
  std::string file( ".\\Maps\\Level" );
  for( uint16_t i = 0; i < 3 - std::to_string( levelNum ).size(); i++ ) {
    file += std::string( "0" );
  }
  file += std::to_string( levelNum ) + std::string( ".sfmap" );

  FILE* mapIn = fopen( file.c_str(), "rb" );
  if( !mapIn ) {
    return NULL;
  }

  char sflvltext[5];
  fread( sflvltext, sizeof( char ), 5, mapIn );
  char sflvlCompare[] = { 'S', 'F', 'L', 'v', 'l' };
  if( 0 != memcmp( sflvltext, sflvlCompare, 5 ) ) {
    fclose( mapIn );
    return NULL;
  }

  uint16_t mapWidth;
  uint16_t mapHeight;
  fread( &mapWidth, sizeof( uint8_t ), 2, mapIn );
  fread( &mapHeight, sizeof( uint8_t ), 2, mapIn );
  game::Level* ret = new game::Level( mapWidth, mapHeight );

  char bgmsep[1];
  fread( bgmsep, sizeof( char ), 1, mapIn );
  char bgmCompare[] = { '\"' };
  if( 0 != memcmp( bgmsep, bgmCompare, 1 ) ) {
    fclose( mapIn );
    return NULL;
  }
  std::string bgmName( "" );
  int c;
  while( ( c = fgetc( mapIn ) ) != (int)'\"' ) {
    char tmp[] = { (char)c, (char)0 };
    bgmName += std::string( tmp );
  }
  bgmPlayer->loadBGM( bgmName.c_str() );

  uint16_t entityCount;
  fread( &entityCount, sizeof( uint8_t ), 2, mapIn );
  for( uint16_t entityI = 0; entityI < entityCount; entityI++ ) {
    uint16_t entityId;
    uint16_t entityXCoord;
    uint16_t entityYCoord;
    uint16_t entityXSize;
    uint16_t entityYSize;
    int16_t entityMaxHealth;
    bool entityMoveVertical;
    uint16_t entityMoveRadius;
    fread( &entityId, sizeof( uint8_t ), 2, mapIn );
    fread( &entityXCoord, sizeof( uint8_t ), 2, mapIn );
    fread( &entityYCoord, sizeof( uint8_t ), 2, mapIn );
    fread( &entityXSize, sizeof( uint8_t ), 2, mapIn );
    fread( &entityYSize, sizeof( uint8_t ), 2, mapIn );
    fread( &entityMaxHealth, sizeof( uint8_t ), 2, mapIn );
    fread( &entityMoveVertical, sizeof( bool ), 1, mapIn );
    fread( &entityMoveRadius, sizeof( uint8_t ), 2, mapIn );

    if( entityId == 0 ) {
      ret->addEntity( new EnemyEntity( entityXCoord, entityYCoord, entityXSize, entityYSize, entityMaxHealth, entityMoveVertical, entityMoveRadius ) );
    }
  }

  uint16_t rowCount;
  fread( &rowCount, sizeof( uint8_t ), 2, mapIn );

  uint16_t tileCount;
  for( uint16_t row = 0; row < rowCount; row++ ) {
    fread( &tileCount, sizeof( uint8_t ), 2, mapIn );

    for( uint16_t tile = 0; tile < tileCount; tile++ ) {
      uint16_t tileName;
      fread( &tileName, sizeof( uint8_t ), 2, mapIn );
      if( tileName == 0 ) {
        // Empty Tile
        // ret->setTile(tile, row - 1, new EmptyTile());
      } else {
        uint16_t tileType;
        uint32_t tileColor;
        fread( &tileType, sizeof( uint8_t ), 2, mapIn );
        fread( &tileColor, sizeof( uint8_t ), 4, mapIn );
        if( tileName == 1 ) {
          // Transition Tile
          uint16_t transitionToX, transitionToY, transitionToLevelID;
          fread( &transitionToX, sizeof( uint8_t ), 2, mapIn );
          fread( &transitionToY, sizeof( uint8_t ), 2, mapIn );
          fread( &transitionToLevelID, sizeof( uint8_t ), 2, mapIn );
          ret->setTile( tile, row - 1, new TransitionTile( transitionToX, transitionToY, transitionToLevelID, tileType, tileColor ) );
        } else if( tileName == 2 ) {
          // Wall Tile
          int tileTerrainType;
          fread( &tileTerrainType, sizeof( uint8_t ), 4, mapIn );
          ret->setTile( tile, row - 1, new WallTile( tileType, tileColor, tileTerrainType ) );
        } else if( tileName == 3 ) {
          // Water Tile
          ret->setTile( tile, row - 1, new WaterTile( tileType, tileColor ) );
        }
      }
    }
  }
  fclose( mapIn );
  return ret;
}

void Map::updateEntities( uint64_t msSinceLastFrame ) {
  selectedLevel->updateEntities();
  for( uint16_t i = 0; i < selectedLevel->getEntities().size(); i++ ) {
    selectedLevel->getEntities()[i]->updatePosition( msSinceLastFrame, this );
  }
}

} /* namespace game */
