#include "Level.h"

void Level::importDataForLevel(int level)
{
	std::cout << "\n";
	std::cout << "\nImporting XML ";
	XMLError eResult = xmlDoc.LoadFile("Resources/LevelData/level1.xml");
	XMLCheckResult(eResult);

	XMLNode* pRoot = xmlDoc.FirstChild();

	if (pRoot == nullptr) std::cout<< "\nXMLERROR: " << XML_ERROR_FILE_READ_ERROR;
	else  std::cout << "\nXML SUCCESS1: " << XML_SUCCESS;

	//XMLElement* pElement = pRoot->FirstChildElement("Level");
	//if (pElement == nullptr)  std::cout << "\nXMLERROR: " << XML_ERROR_PARSING_ELEMENT;
	//else  std::cout << "\nXML SUCCESS2: " << XML_SUCCESS;

	//int iOutInt;
	//eResult = pElement->QueryIntText(&iOutInt);
	//XMLCheckResult(eResult);

	//return XMLError::XML_SUCCESS;


	/*float fOutFloat;
	eResult = pElement->QueryFloatText(&fOutFloat);
	*/
	std::cout << "\nEnding import " ;
	
}

Level::Level()
{
	
}

Level::~Level()
{
}
