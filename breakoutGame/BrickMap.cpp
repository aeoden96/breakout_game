#include "BrickMap.h"

void BrickMap::clear()
{
	for (size_t x = 0; x < this->maxSize.x; x++)
	{
		for (size_t y = 0; y < maxSize.y; y++)
		{
			for (size_t z = 0; z < this->layers; z++)
			{
				delete this->map[x][y][z];
				this->map[x][y][z] = NULL;
			}
			this->map[x][y].clear();
		}
		this->map[x].clear();
	}
	this->map.clear();


}

Brick* BrickMap::returnBrick(int i,int j) {
	return this->map[i][j][0];
}

void BrickMap::crackIt(int i, int j)
{
	//number of hits still required
	int crackNum = this->map[i][j][0]->getCrackNum();

	char type = this->map[i][j][0]->getBrickType();

	crackNum = this->levelInfo->brickMap.at(type).hitPoints - crackNum;

	int brickIndex = brickTypeClass::getIndex(type);

	bool isCracked = crackNum == 1;

	this->map[i][j][0]->crackIt(400 * brickIndex, 200*(crackNum+1), this->gridSizeU, (int)(this->gridSizeU * 0.5f));


	this->playSound(isCracked, type);
	
}


BrickMap::BrickMap(float gridSize,
	unsigned screen_width, unsigned screen_height,
	std::string textureFile, 
	XML_Level* levelInfo,
	ScoreSystem* scoreSystem)
{
	this->scoreSystem = scoreSystem;
	this->levelInfo = levelInfo;
	this->textureFile = textureFile;
	std::string brickAlignment =this->levelInfo->brickAlignment;

	if (!this->tileTextureSheet.loadFromFile(textureFile))
		std::cout << "ERROR:TILEMAP:FAILED_TO_LOAD_TILE_TEXTURE_SHEET::FILENAME:" << textureFile << "\n";

	enum BRICK_TYPE { M,H,I,S,EMPTY};
	for (std::pair<char, BrickType> b : this->levelInfo->brickMap) {
		
		if (!this->breakSounds[b.first].openFromFile(b.second.breakSound))
			return; // error

		if (!this->hitSounds[b.first].openFromFile(b.second.hitSound))
			return; // error

	}
	//this->sound.setBuffer(*sb);
	this->gridSizeF = gridSize;
	this->gridSizeU = static_cast<unsigned>(this->gridSizeF);
	this->maxSize.x = this->levelInfo->columnCount;
	this->maxSize.y = this->levelInfo->rowCount;
	this->layers = 1;

	this->map.resize(this->maxSize.x, std::vector<  std::vector<Brick*>>());

	for (size_t x = 0; x < this->maxSize.x; x++)
	{
		for (size_t y = 0; y < maxSize.y; y++)
		{
			this->map[x].resize(this->maxSize.y, std::vector<Brick*>());

			for (size_t z = 0; z < this->layers; z++)
			{
				this->map[x][y].resize(this->layers, NULL);
			}
		}
	}


	int brickIndex;
	char brickType;
	int red = 0;
	int stupac = 0;


	for (char& c : brickAlignment) {

		if (c != ' ' && c != '\n') {
			stupac++;
			brickType = c;
			brickIndex = brickTypeClass::getIndex(brickType);
		}
		else if(c == '\n') {
			if (stupac == 0 && red == 0)
				continue;
			red++;
			stupac = 0;
		}
		else {
			continue;
		}

		int offset = this->levelInfo->columnSpacing;

		float brickW = static_cast<float>(screen_width - offset * (maxSize.x + 1)) / maxSize.x;

		if (c != ' ' && c != '\n') {
			stupac--;


			this->map[stupac][red][0] =
				new Brick(
					stupac,
					red,
					brickW,
					(screen_height / 20.f),
					this->tileTextureSheet,
					sf::IntRect(
						this->gridSizeU * brickIndex,
						0,
						this->gridSizeU,
						static_cast<int>(this->gridSizeU * 0.5f) ),
					true,
					0,
					brickType,
					levelInfo->brickMap.at(brickType).hitPoints
				);
			stupac++;
		}

	}
}

BrickMap::~BrickMap()
{
	this->clear();
}

const sf::Texture* BrickMap::getTileSheet() const
{
	return &this->tileTextureSheet;
}

//Functions
void BrickMap::update()
{
}

void BrickMap::render(sf::RenderTarget& target)
{
	for (auto& x : this->map)
	{
		for (auto& y : x)
		{
			for (auto* z : y)
			{
				if (z != nullptr)
					z->render(target);
			}
		}
	}
}

void BrickMap::playSound(bool brickBroken, char brickType)
{
	if (brickBroken) {
		this->breakSounds.at(brickType).stop();
		this->breakSounds.at(brickType).play();
	}
	else {
		this->hitSounds.at(brickType).stop();
		this->hitSounds.at(brickType).play();
	}

}

void BrickMap::addTile(
	const unsigned x,
	const unsigned y,
	const unsigned z,
	const sf::IntRect& tex_rect,
	const bool& collision, 
	const bool& type)
{
	/*Take three indicies from mouse pos in the grid and add tile to that pos
	if internal tilemap array allows it*/

	if (x < this->maxSize.x &&
		y < this->maxSize.y &&
		x >= 0 &&
		y >= 0 &&
		z < this->layers &&
		z >= 0)
	{
		if (this->map[x][y][z] == NULL)
		{
			/*OK to add tile.*/
			//this->map[x][y][z] = new Brick(x, y, this->gridSizeF, this->tileTextureSheet, tex_rect, collision, type);
			std::cout << "DEBUG: ADDED TILE\n ";
		}
	}
}

void BrickMap::removeTile(const unsigned x, const unsigned y, const unsigned z)
{
	/*Take three indicies from mouse pos in the grid and remove tile to that pos
	if internal tilemap array allows it*/

	if (x < this->maxSize.x &&
		y < this->maxSize.y &&
		x >= 0 &&
		y >= 0 &&
		z < this->layers &&
		z >= 0)
	{
		if (this->map[x][y][z] != NULL)
		{
			/*OK to remove tile.*/
			delete this->map[x][y][z];
			this->map[x][y][z] = NULL;
			std::cout << "DEBUG: REMOVED TILE\n ";
		}
	}

}

void BrickMap::saveToFile(const std::string fileName)
{
	/*saves the entire tilemap to text-file
	Format:
	Basic:
	Size x y
	gridSize
	layers
	textureFile
	All tiles:
	gridPos x y layer, textureRect x y ,collision, type
	*/

	std::ofstream out_file;

	out_file.open(fileName);

	if (out_file.is_open())
	{
		out_file << this->maxSize.x << " " << this->maxSize.y << "\n"
			<< this->gridSizeU << "\n"
			<< this->layers << "\n"
			<< this->textureFile << "\n";

		for (size_t x = 0; x < this->maxSize.x; x++)
		{
			for (size_t y = 0; y < maxSize.y; y++)
			{
				for (size_t z = 0; z < this->layers; z++)
				{
					if (this->map[x][y][z])
						out_file << x << " " << y << " " << z << " " << this->map[x][y][z]->getAsString() << " "; //MAKE SURE LAST SPACE IS NOT SAVED
				}
			}
		}
	}
	else
	{
		std::cout << "ERROR:TILEMAP:COULD_NOT_SAVE_TO_FILE::FILENAME:" << fileName << "\n";
	}

	out_file.close();
}

void BrickMap::loadFromFile(const std::string fileName)
{
	
	std::ifstream in_file;

	in_file.open(fileName);

	if (in_file.is_open())
	{
		sf::Vector2u size;
		unsigned gridSize = 0;
		unsigned layers = 0;
		std::string textureFile = "";
		unsigned x = 0;
		unsigned y = 0;
		unsigned z = 0;
		unsigned trX = 0;
		unsigned trY = 0;
		bool collision = false;
		short type = 0;

		//Basics
		in_file >> size.x >> size.y >> gridSize >> layers >> textureFile;


		//Tiles
		this->gridSizeF = static_cast<float>(gridSize);
		this->gridSizeU = gridSize;
		this->maxSize.x = size.x;
		this->maxSize.y = size.y;
		this->layers = layers;
		this->textureFile = textureFile;

		std::cout << "LOADED " << size.x << " " << size.x << " " << gridSizeU << " " << layers << " " << textureFile << "\n";

		
		this->clear();

		/*instead of pushback, we are using resize to set values in the map at once*/
		this->map.resize(this->maxSize.x, std::vector<  std::vector<Brick*>>());

		for (size_t x = 0; x < this->maxSize.x; x++)
		{
			for (size_t y = 0; y < maxSize.y; y++)
			{
				this->map[x].resize(this->maxSize.y, std::vector<Brick*>());

				for (size_t z = 0; z < this->layers; z++)
				{
					this->map[x][y].resize(this->layers, NULL);
				}
			}
		}

		if (!this->tileTextureSheet.loadFromFile(textureFile))
			std::cout << "ERROR:TILEMAP:FAILED_TO_LOAD_TILE_TEXTURE_SHEET::FILENAME:" << textureFile << "\n";

		//Load all tiles
		while (in_file >> x >> y >> z >> trX >> trY >> collision >> type)
		{
			/*this->map[x][y][z] = new Brick(
				x, y,
				gridSizeF,
				this->tileTextureSheet,
				sf::IntRect(trX, trY, this->gridSizeU, this->gridSizeU),
				collision,
				type);*/
			std::cout << "LOADED " << x << " " << y << "\n";
		}

	}
	else
	{
		std::cout << "ERROR:TILEMAP:COULD_LOAD_FROM_FILE::FILENAME:" << fileName << "\n";
	}

	in_file.close();
}

