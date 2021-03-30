#include "XML_Level.h"

void XML_Level::importDataForLevel(int level)
{
	std::cout << "\n";
	std::cout << "\nXML::Import::START\n";
	

	XMLNode* pRoot = xmlDoc->FirstChild();

	

	if (pRoot == nullptr) {
		std::cout << "\nXMLERROR: " << XML_ERROR_FILE_READ_ERROR;
		return;
	}
		
	else  std::cout << "\nXML SUCCESS1: pRoot exists";

	//std::cout << "\n"<< pRoot->Value() << "\n";  // "Level"

	this->rowCount = std::stoi(
		((XMLElement*)pRoot)->Attribute("RowCount"));

	this->columnCount = std::stoi(
		((XMLElement*)pRoot)->Attribute("ColumnCount"));

	this->rowSpacing = std::stoi(
		((XMLElement*)pRoot)->Attribute("RowSpacing"));

	this->columnSpacing = std::stoi(
		((XMLElement*)pRoot)->Attribute("ColumnSpacing"));

	this->backgroundTexture = ((XMLElement*)pRoot)->Attribute("BackgroundTexture");

	//std::cout << "\n" << this->backgroundTexture << "\n";  // "Level"

	XMLElement* brickTypes = pRoot->FirstChildElement("BrickTypes");

	if (brickTypes == nullptr)  std::cout << "\nXMLERROR: " << XML_ERROR_PARSING_ELEMENT;
	else  std::cout << "\nXML SUCCESS2: " << XML_SUCCESS;

	XMLElement* brickType = brickTypes->FirstChildElement("BrickType");

	
	BrickType temp;

	bool isFirst = true;
	while (true) {

		if (isFirst) {
			brickType = brickTypes->FirstChildElement("BrickType");
			isFirst = false;
		}
		else
			brickType = brickType->NextSiblingElement("BrickType");
		
		if (brickType == nullptr) break;


		temp.id =			brickType->Attribute("Id");
		temp.texture =		brickType->Attribute("Texture");
		temp.breakSound=	brickType->Attribute("BreakSound");
		temp.hitPoints =	brickType->Attribute("HitPoints");
		temp.hitSound =		brickType->Attribute("HitSound");
		temp.breakScore=	std::stoi(brickType->Attribute("BreakScore"));

		this->brickTypes.push_back(temp);

	}

	std::cout << "\nFIN brick info\n";

	XMLElement* brickOrg = brickTypes->NextSiblingElement("Bricks");
	this->brickAlignment=brickOrg->GetText();


	std::cout << "\n" << this->backgroundTexture;


	//int iOutInt;
	//eResult = pElement->QueryIntText(&iOutInt);
	//XMLCheckResult(eResult);

	//return XMLError::XML_SUCCESS;


	/*float fOutFloat;
	eResult = pElement->QueryFloatText(&fOutFloat);
	*/
	std::cout << "\nXML::Import::STOP\n" ;
	
}

XML_Level::XML_Level(std::string location)
{
	xmlDoc = new XMLDocument();

	XMLError eResult = xmlDoc->LoadFile(location.c_str());
	XMLCheckResult(eResult);
	
}

XML_Level::~XML_Level()
{
	delete xmlDoc;
}
