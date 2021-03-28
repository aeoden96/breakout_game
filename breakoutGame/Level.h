#pragma once

#include "libs.h"

#include "tinyxml2.h"
using namespace tinyxml2;

#ifndef XMLCheckResult
#define XMLCheckResult(a_eResult) if (a_eResult != XML_SUCCESS) { printf("Error: %i\n", a_eResult);  }
#endif

class Level
{
	
	XMLDocument xmlDoc;

	int rowCount;
	int columnCount;
	int rowSpacing;
	int columnSpacing;
	std::string backgroundTexture;

public:
	void importDataForLevel(int level);
	Level();
	~Level();

};

