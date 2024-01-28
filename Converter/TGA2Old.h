/*
 * TGA2Old.h
 *
 *  Created on: 11.03.2017
 *      Author: SFG
 */

#ifndef TGA2OLD_H_
#define TGA2OLD_H_

#include <iostream>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <string>

#include "../pugiXML/pugixml.hpp"


bool tga2Old( const char* pathToTGA ) {
  FILE* fileIn = fopen( pathToTGA, "rb" );
  if( !fileIn ) {
    return false;
  }

  uint16_t imageIdLength = fgetc( fileIn );

  uint16_t colorPallete = fgetc( fileIn );

  uint16_t imageType = fgetc( fileIn );

  uint16_t palleteBegin = fgetc( fileIn ) + ( fgetc( fileIn ) << 8 );

  uint16_t palleteLength = fgetc( fileIn ) + ( fgetc( fileIn ) << 8 );

  uint16_t palleteSize = fgetc( fileIn );

  uint16_t xNull = fgetc( fileIn ) + ( fgetc( fileIn ) << 8 );

  uint16_t yNull = fgetc( fileIn ) + ( fgetc( fileIn ) << 8 );

  uint16_t imageWidth = fgetc( fileIn ) + ( fgetc( fileIn ) << 8 );

  uint16_t imageHeight = fgetc( fileIn ) + ( fgetc( fileIn ) << 8 );

  uint16_t bitsPerPixel = fgetc( fileIn );

  uint16_t attribute = fgetc( fileIn );

  //-----------------------------------------------------------------------------------------------------------------

  std::string filename( pathToTGA );
  filename.resize( filename.find_last_of( '.' ) );
  filename += std::string( ".xml" );
  pugi::xml_document docOut;

  docOut.append_child( "Level" );

  docOut.child( "Level" ).append_attribute( "width" );
  docOut.child( "Level" ).append_attribute( "height" );
  docOut.child( "Level" ).append_attribute( "bgm" );
  docOut.child( "Level" ).attribute( "height" ) = imageHeight;
  docOut.child( "Level" ).attribute( "width" ) = imageWidth;
  docOut.child( "Level" ).attribute( "bgm" ) = "8bit 01 wo.wav";

  uint16_t red, green, blue, alpha;
  uint32_t color;

  for( uint16_t y = 0; y < imageHeight; y++ ) {
    docOut.child( "Level" ).prepend_child( "Row" );
    for( uint16_t x = 0; x < imageWidth; x++ ) {
      blue = fgetc( fileIn );
      green = fgetc( fileIn );
      red = fgetc( fileIn );
      alpha = fgetc( fileIn );
      color = ( ( red & 0xFF ) << 24 ) + ( ( green & 0xFF ) << 16 ) + ( ( blue & 0xFF ) << 8 ) + ( alpha & 0xFF );
      if( red == 0 && green == 0 && blue == 0 ) {
        docOut.child( "Level" ).first_child().append_child( "EmptyTile" );
      } else if( red == 255 && green == 255 && blue == 0 ) {
        docOut.child( "Level" ).first_child().append_child( "TransitionTile" );
        docOut.child( "Level" ).first_child().last_child().append_attribute( "xTo" );
        docOut.child( "Level" ).first_child().last_child().append_attribute( "yTo" );
        docOut.child( "Level" ).first_child().last_child().append_attribute( "levelIndexTo" );
        docOut.child( "Level" ).first_child().last_child().append_attribute( "tileType" );
        docOut.child( "Level" ).first_child().last_child().append_attribute( "tileColor" );
        docOut.child( "Level" ).first_child().last_child().append_attribute( "tileTerrainType" );
        docOut.child( "Level" ).first_child().last_child().attribute( "xTo" ) = 0;
        docOut.child( "Level" ).first_child().last_child().attribute( "yTo" ) = 0;
        docOut.child( "Level" ).first_child().last_child().attribute( "levelIndexTo" ) = 0;
        docOut.child( "Level" ).first_child().last_child().attribute( "tileType" ) = 1;
        docOut.child( "Level" ).first_child().last_child().attribute( "tileColor" ) = color;
        docOut.child( "Level" ).first_child().last_child().attribute( "tileTerrainType" ) = 1;
      } else if( red == 0 && green == 0 && blue == 255 ) {
        docOut.child( "Level" ).first_child().append_child( "WaterTile" );
        docOut.child( "Level" ).first_child().last_child().append_attribute( "tileType" );
        docOut.child( "Level" ).first_child().last_child().append_attribute( "tileColor" );
        docOut.child( "Level" ).first_child().last_child().attribute( "tileType" ) = 0;
        docOut.child( "Level" ).first_child().last_child().attribute( "tileColor" ) = color;
      } else {
        docOut.child( "Level" ).first_child().append_child( "WallTile" );
        docOut.child( "Level" ).first_child().last_child().append_attribute( "tileType" );
        docOut.child( "Level" ).first_child().last_child().append_attribute( "tileColor" );
        docOut.child( "Level" ).first_child().last_child().append_attribute( "tileTerrainType" );
        docOut.child( "Level" ).first_child().last_child().attribute( "tileType" ) = 1;
        docOut.child( "Level" ).first_child().last_child().attribute( "tileColor" ) = color;
        docOut.child( "Level" ).first_child().last_child().attribute( "tileTerrainType" ) = 1;
      }
    }
  }
  docOut.child( "Level" ).prepend_child( "Entities" );

  docOut.save_file( filename.c_str(), " ", 0, pugi::encoding_utf8 );

  return true;
}

#endif /* TGA2OLD_H_ */
