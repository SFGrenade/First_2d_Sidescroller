/*
 * Old2New.h
 *
 *  Created on: 11.03.2017
 *      Author: SFG
 */

#ifndef OLD2NEW_H_
#define OLD2NEW_H_

#include <iostream>
#include <string>
#include <vector>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "../pugiXML/pugixml.hpp"

using namespace std;

bool old2New(const char* pathToOldMap) {
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file(pathToOldMap);
	if (result.status != pugi::status_ok) {
		return false;
	}

	std::string filename(pathToOldMap);
	filename.resize(filename.find_last_of('.'));
	filename += std::string(".sfmap");
	FILE* fileOut = fopen(filename.c_str(), "wb");
	if (!fileOut) {
		return false;
	}

	std::string fileOutBegin("SFLvl");
	uint16_t mapWidth, mapHeight;
	std::string mapBGM("");
	mapWidth = (uint16_t) doc.first_child().attribute("width").as_uint();
	mapHeight = (uint16_t) doc.first_child().attribute("height").as_uint();
	mapBGM += std::string("\"");
	mapBGM += std::string(doc.first_child().attribute("bgm").as_string());
	mapBGM += std::string("\"");

	typedef struct {
		uint16_t id;
		uint16_t xCoord;
		uint16_t yCoord;
		uint16_t xSize;
		uint16_t ySize;
		int16_t maxHealth;
		bool moveVertical;
		uint16_t moveRadius;
	} EntityStruct;

	std::vector<EntityStruct> entities;
	for (pugi::xml_node::iterator rowIter = doc.first_child().first_child().begin(); rowIter != doc.first_child().first_child().end(); rowIter++) {
		if (!strcmp((*rowIter).name(), "EnemyEntity")) {
			entities.push_back(EntityStruct {
						(uint16_t) 0,
						(uint16_t) (*rowIter).attribute("x").as_uint(),
						(uint16_t) (*rowIter).attribute("y").as_uint(),
						(uint16_t) (*rowIter).attribute("size-x").as_uint(),
						(uint16_t) (*rowIter).attribute("size-y").as_uint(),
						(int16_t) (*rowIter).attribute("max-health").as_int(),
						(bool) (*rowIter).attribute("moves-vertical").as_int(),
						(uint16_t) (*rowIter).attribute("move-radius").as_int()
			});
		}
	}
	uint16_t entityCount = entities.size();

	typedef struct {
		uint16_t tileName;
		uint16_t tileType;
		uint32_t tileColor;
		int tileTerrainType;
		uint16_t transitionToX;
		uint16_t transitionToY;
		uint16_t transitionToLevelID;
	} TileStruct;

	std::vector<std::vector<TileStruct> > rows;
	int y = 0;
	for (pugi::xml_node::iterator rowIter = doc.first_child().begin(); rowIter != doc.first_child().end(); rowIter++) {
		rows.push_back(std::vector<TileStruct>());
		for (pugi::xml_node::iterator tileIter = (*rowIter).begin(); tileIter != (*rowIter).end(); tileIter++) {
			if (!strcmp((*tileIter).name(), "EmptyTile")) {
				rows[y].push_back(TileStruct { (uint16_t) 0, (uint16_t) 0, (uint32_t) 0x00000000, (int) 0, (uint16_t) 0, (uint16_t) 0, (uint16_t) 0 });
			} else if (!strcmp((*tileIter).name(), "TransitionTile")) {
				rows[y].push_back(TileStruct { (uint16_t) 1, (uint16_t) (*tileIter).attribute("tileType").as_uint(), (uint32_t) (*tileIter).attribute("tileColor").as_uint(), (int) 1, (uint16_t) (*tileIter).attribute("xTo").as_uint(), (uint16_t) (*tileIter).attribute("yTo").as_uint(), (uint16_t) (*tileIter).attribute("levelIndexTo").as_uint() });
			} else if (!strcmp((*tileIter).name(), "WallTile")) {
				rows[y].push_back(TileStruct { (uint16_t) 2, (uint16_t) (*tileIter).attribute("tileType").as_uint(), (uint32_t) (*tileIter).attribute("tileColor").as_uint(), (int) (*tileIter).attribute("tileTerrainType").as_int(), (uint16_t) 0, (uint16_t) 0, (uint16_t) 0 });
			} else if (!strcmp((*tileIter).name(), "WaterTile")) {
				rows[y].push_back(TileStruct { (uint16_t) 3, (uint16_t) (*tileIter).attribute("tileType").as_uint(), (uint32_t) (*tileIter).attribute("tileColor").as_uint(), (int) 2, (uint16_t) 0, (uint16_t) 0, (uint16_t) 0 });
			}
		}
		y++;
	}
	uint16_t rowCount = rows.size();

	fwrite(fileOutBegin.c_str(), fileOutBegin.size(), 1, fileOut);
	uint8_t mapWidth1 = (mapWidth & 0x00FF);
	uint8_t mapWidth2 = (mapWidth & 0xFF00) >> 8;
	fwrite(&mapWidth1, sizeof(mapWidth1), 1, fileOut);
	fwrite(&mapWidth2, sizeof(mapWidth2), 1, fileOut);
	uint8_t mapHeight1 = (mapHeight & 0x00FF);
	uint8_t mapHeight2 = (mapHeight & 0xFF00) >> 8;
	fwrite(&mapHeight1, sizeof(mapHeight1), 1, fileOut);
	fwrite(&mapHeight2, sizeof(mapHeight2), 1, fileOut);
	fwrite(mapBGM.c_str(), mapBGM.size(), 1, fileOut);

	uint8_t entityCount1 = (entityCount & 0x00FF);
	uint8_t entityCount2 = (entityCount & 0xFF00) >> 8;
	fwrite(&entityCount1, sizeof(entityCount1), 1, fileOut);
	fwrite(&entityCount2, sizeof(entityCount2), 1, fileOut);
	for (uint16_t i = 0; i < entityCount; i++) {
		uint8_t entityId1 = (entities[i].id & 0x00FF);
		uint8_t entityId2 = (entities[i].id & 0xFF00) >> 8;
		fwrite(&entityId1, sizeof(entityId1), 1, fileOut);
		fwrite(&entityId2, sizeof(entityId2), 1, fileOut);

		uint8_t entityXCoord1 = (entities[i].xCoord & 0x00FF);
		uint8_t entityXCoord2 = (entities[i].xCoord & 0xFF00) >> 8;
		fwrite(&entityXCoord1, sizeof(entityXCoord1), 1, fileOut);
		fwrite(&entityXCoord2, sizeof(entityXCoord2), 1, fileOut);

		uint8_t entityYCoord1 = (entities[i].yCoord & 0x00FF);
		uint8_t entityYCoord2 = (entities[i].yCoord & 0xFF00) >> 8;
		fwrite(&entityYCoord1, sizeof(entityYCoord1), 1, fileOut);
		fwrite(&entityYCoord2, sizeof(entityYCoord2), 1, fileOut);

		uint8_t entityXSize1 = (entities[i].xSize & 0x00FF);
		uint8_t entityXSize2 = (entities[i].xSize & 0xFF00) >> 8;
		fwrite(&entityXSize1, sizeof(entityXSize1), 1, fileOut);
		fwrite(&entityXSize2, sizeof(entityXSize2), 1, fileOut);

		uint8_t entityYSize1 = (entities[i].ySize & 0x00FF);
		uint8_t entityYSize2 = (entities[i].ySize & 0xFF00) >> 8;
		fwrite(&entityYSize1, sizeof(entityYSize1), 1, fileOut);
		fwrite(&entityYSize2, sizeof(entityYSize2), 1, fileOut);

		uint8_t entityMaxHealth1 = (entities[i].maxHealth & 0x00FF);
		uint8_t entityMaxHealth2 = (entities[i].maxHealth & 0xFF00) >> 8;
		fwrite(&entityMaxHealth1, sizeof(entityMaxHealth1), 1, fileOut);
		fwrite(&entityMaxHealth2, sizeof(entityMaxHealth2), 1, fileOut);

		fwrite(&(entities[i].moveVertical), sizeof(entities[i].moveVertical), 1, fileOut);

		uint8_t entityMoveRadius1 = (entities[i].moveRadius & 0x00FF);
		uint8_t entityMoveRadius2 = (entities[i].moveRadius & 0xFF00) >> 8;
		fwrite(&entityMoveRadius1, sizeof(entityMoveRadius1), 1, fileOut);
		fwrite(&entityMoveRadius2, sizeof(entityMoveRadius2), 1, fileOut);
	}

	uint8_t rowCount1 = (rowCount & 0x00FF);
	uint8_t rowCount2 = (rowCount & 0xFF00) >> 8;
	fwrite(&rowCount1, sizeof(rowCount1), 1, fileOut);
	fwrite(&rowCount2, sizeof(rowCount2), 1, fileOut);
	uint16_t rowSize;
	for (uint16_t y = 0; y < rowCount; y++) {
		rowSize = rows[y].size();
		uint8_t rowSize1 = (rowSize & 0x00FF);
		uint8_t rowSize2 = (rowSize & 0xFF00) >> 8;
		fwrite(&rowSize1, sizeof(rowSize1), 1, fileOut);
		fwrite(&rowSize2, sizeof(rowSize2), 1, fileOut);
		for (uint16_t x = 0; x < rowSize; x++) {
			uint8_t tileName1 = (rows[y][x].tileName & 0x00FF);
			uint8_t tileName2 = (rows[y][x].tileName & 0xFF00) >> 8;
			fwrite(&tileName1, sizeof(tileName1), 1, fileOut);
			fwrite(&tileName2, sizeof(tileName2), 1, fileOut);
			if (rows[y][x].tileName == 0) {
				// Empty Tile
				// Done
			} else {
				uint8_t tileType1 = (rows[y][x].tileType & 0x00FF);
				uint8_t tileType2 = (rows[y][x].tileType & 0xFF00) >> 8;
				fwrite(&tileType1, sizeof(tileType1), 1, fileOut);
				fwrite(&tileType2, sizeof(tileType2), 1, fileOut);
				uint8_t tileColor1 = (rows[y][x].tileColor & 0x000000FF);
				uint8_t tileColor2 = (rows[y][x].tileColor & 0x0000FF00) >> 8;
				uint8_t tileColor3 = (rows[y][x].tileColor & 0x00FF0000) >> 16;
				uint8_t tileColor4 = (rows[y][x].tileColor & 0xFF000000) >> 24;
				fwrite(&tileColor1, sizeof(tileColor1), 1, fileOut);
				fwrite(&tileColor2, sizeof(tileColor2), 1, fileOut);
				fwrite(&tileColor3, sizeof(tileColor3), 1, fileOut);
				fwrite(&tileColor4, sizeof(tileColor4), 1, fileOut);
				if (rows[y][x].tileName == 1) {
					// Transition Tile
					uint8_t transitionToX1 = (rows[y][x].transitionToX & 0x00FF);
					uint8_t transitionToX2 = (rows[y][x].transitionToX & 0xFF00) >> 8;
					fwrite(&transitionToX1, sizeof(transitionToX1), 1, fileOut);
					fwrite(&transitionToX2, sizeof(transitionToX2), 1, fileOut);
					uint8_t transitionToY1 = (rows[y][x].transitionToY & 0x00FF);
					uint8_t transitionToY2 = (rows[y][x].transitionToY & 0xFF00) >> 8;
					fwrite(&transitionToY1, sizeof(transitionToY1), 1, fileOut);
					fwrite(&transitionToY2, sizeof(transitionToY2), 1, fileOut);
					uint8_t transitionToLevelID1 = (rows[y][x].transitionToLevelID & 0x00FF);
					uint8_t transitionToLevelID2 = (rows[y][x].transitionToLevelID & 0xFF00) >> 8;
					fwrite(&transitionToLevelID1, sizeof(transitionToLevelID1), 1, fileOut);
					fwrite(&transitionToLevelID2, sizeof(transitionToLevelID2), 1, fileOut);
					// Done
				} else if (rows[y][x].tileName == 2) {
					// Wall Tile
					uint8_t tileTerrainType1 = (rows[y][x].tileTerrainType & 0x000000FF);
					uint8_t tileTerrainType2 = (rows[y][x].tileTerrainType & 0x0000FF00) >> 8;
					uint8_t tileTerrainType3 = (rows[y][x].tileTerrainType & 0x00FF0000) >> 16;
					uint8_t tileTerrainType4 = (rows[y][x].tileTerrainType & 0xFF000000) >> 24;
					fwrite(&tileTerrainType1, sizeof(tileTerrainType1), 1, fileOut);
					fwrite(&tileTerrainType2, sizeof(tileTerrainType2), 1, fileOut);
					fwrite(&tileTerrainType3, sizeof(tileTerrainType3), 1, fileOut);
					fwrite(&tileTerrainType4, sizeof(tileTerrainType4), 1, fileOut);
					// Done
				} else if (rows[y][x].tileName == 3) {
					// Water Tile
					// Done
				}
			}
		}
	}

	return true;
}

#endif /* OLD2NEW_H_ */
