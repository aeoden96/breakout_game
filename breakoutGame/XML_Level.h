#pragma once

#include "libs.h"
#include"External/TinyXML/tinyxml2.h"

using namespace tinyxml2;

#ifndef XMLCheckResult
#define XMLCheckResult(a_eResult) if (a_eResult != XML_SUCCESS) { printf("Error: %i\n", a_eResult);  }
#endif




struct BrickType {
	char id;
	std::string texture;
	unsigned int hitPoints;
	std::string hitSound;
	std::string breakSound;
	unsigned int breakScore;
};

class XML_Level
{
public:
	//std::vector<BrickType> brickTypes;
	std::map<char, BrickType> brickMap;
	std::string brickAlignment;
	std::string location;
	XMLDocument* xmlDoc;

	int rowCount;
	int columnCount;
	int rowSpacing;
	int columnSpacing;
	std::string backgroundTexture;

	void importDataForLevel(int level);
	XML_Level();
	~XML_Level();

};

