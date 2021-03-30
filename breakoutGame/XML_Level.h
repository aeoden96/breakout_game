#pragma once

#include "libs.h"

#include "tinyxml2.h"
using namespace tinyxml2;

#ifndef XMLCheckResult
#define XMLCheckResult(a_eResult) if (a_eResult != XML_SUCCESS) { printf("Error: %i\n", a_eResult);  }
#endif

struct BrickType {
	std::string id;
	std::string texture;
	std::string hitPoints;
	std::string hitSound;
	std::string breakSound;
	int breakScore;
};

class XML_Level
{
public:
	std::vector<BrickType> brickTypes;
	std::string brickAlignment;

	XMLDocument* xmlDoc;

	int rowCount;
	int columnCount;
	int rowSpacing;
	int columnSpacing;
	std::string backgroundTexture;


	void importDataForLevel(int level);
	XML_Level(std::string location);
	~XML_Level();

};

