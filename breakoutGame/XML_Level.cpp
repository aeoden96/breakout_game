#include "XML_Level.h"

void XML_Level::importDataForLevel(int level)
{
	std::string path = location + std::to_string(level) + ".xml";
	XMLError eResult = xmlDoc->LoadFile(path.c_str());
	XMLCheckResult(eResult);

	this->brickMap.clear();

	

	XMLNode* pRoot = xmlDoc->FirstChild();

	

	if (pRoot == nullptr) {
		std::cout << "\nXMLERROR: " << XML_ERROR_FILE_READ_ERROR;
		return;
	}

	this->rowCount = std::stoi(
		((XMLElement*)pRoot)->Attribute("RowCount"));

	this->columnCount = std::stoi(
		((XMLElement*)pRoot)->Attribute("ColumnCount"));

	this->rowSpacing = std::stoi(
		((XMLElement*)pRoot)->Attribute("RowSpacing"));

	this->columnSpacing = std::stoi(
		((XMLElement*)pRoot)->Attribute("ColumnSpacing"));

	this->backgroundTexture = 
		((XMLElement*)pRoot)->Attribute("BackgroundTexture");


	XMLElement* brickTypes = pRoot->FirstChildElement("BrickTypes");

	if (brickTypes == nullptr)  
		std::cout << "\nXMLERROR: " << XML_ERROR_PARSING_ELEMENT;

	XMLElement* brickType = brickTypes->FirstChildElement("BrickType");
	BrickType temp;
	bool isFirst = true;


	//getting all brick types "BrickType" in node "BrickTypes"
	while (true) {

		if (isFirst) {
			brickType = brickTypes->FirstChildElement("BrickType");
			isFirst = false;
		}
		else
			brickType = brickType->NextSiblingElement("BrickType");
		
		if (brickType == nullptr) break;


		temp.id =			brickType->Attribute("Id")[0];
		temp.texture =		brickType->Attribute("Texture");
		temp.breakSound=	brickType->Attribute("BreakSound");
		temp.hitSound =		brickType->Attribute("HitSound");
		temp.breakScore=	std::stoi(brickType->Attribute("BreakScore"));

		temp.hitPoints = brickType->Attribute("HitPoints")==std::string("Infinite")? 
			10000:
			std::stoi(brickType->Attribute("HitPoints"));
		
		
		this->brickMap.insert(
			std::pair<char, BrickType>(temp.id, temp));


	}
	



	XMLElement* brickOrg = brickTypes->NextSiblingElement("Bricks");

	if (brickOrg == nullptr) {
		std::cout << "\nXMLERROR: " << XML_ERROR_FILE_READ_ERROR;
		return;
	}

	this->brickAlignment=brickOrg->GetText();



	
}

XML_Level::XML_Level()
{
	this->location = "Resources/LevelData/level";
	xmlDoc = new XMLDocument();
	std::string path = location + "1.xml";


	XMLError eResult = xmlDoc->LoadFile(path.c_str());
	XMLCheckResult(eResult);
	this->columnCount = 0;
	this->columnSpacing = 0;
	this->rowCount = 0;
	this->rowSpacing = 0;
	this->brickAlignment = "";


	
}

XML_Level::~XML_Level()
{
	delete xmlDoc;
}
