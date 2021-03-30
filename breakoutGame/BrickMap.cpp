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

int BrickMap::checkCollision(Entity* e)
{
	for (size_t x = 0; x < this->maxSize.x; x++)
	{
		for (size_t y = 0; y < maxSize.y; y++)
		{
			if (e->checkCollision(this->map[x][y][0]->returnPosition()))
			{
				this->map[x][y][0]->hit();
				return 1;
			}
		}
	}


	



	return 0;
}

BrickMap::BrickMap(float gridSize, unsigned width, unsigned height, std::string textureFile)
{
	

	std::cout << "\n" << "TileMap KONSTR ";
	this->textureFile = textureFile;
	this->gridSizeF = gridSize;
	this->gridSizeU = static_cast<unsigned>(this->gridSizeF);
	this->maxSize.x = width;
	this->maxSize.y = height;
	this->layers = 1;

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


	
}

BrickMap::BrickMap(float gridSize, unsigned width, unsigned height, std::string textureFile, XML_Level* levelInfo)
{
	std::cout << "\nBRICKMAP::CONSTRUCTOR";
	this->levelInfo = levelInfo;
	this->textureFile = textureFile;
	std::string brickAlignment =this->levelInfo->brickAlignment;

	if (!this->tileTextureSheet.loadFromFile(textureFile))
		std::cout << "ERROR:TILEMAP:FAILED_TO_LOAD_TILE_TEXTURE_SHEET::FILENAME:" << textureFile << "\n";

	enum BRICK_TYPE { M,H,I,S,EMPTY};


	this->gridSizeF = gridSize;
	this->gridSizeU = static_cast<unsigned>(this->gridSizeF);
	this->maxSize.x = this->levelInfo->columnCount;
	this->maxSize.y = this->levelInfo->rowCount;
	this->layers = 1;



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
	std::cout << "\nMAP SIZE" << this->map.size();
	std::cout << "\nMAP SIZE" << this->map.back().size();

	std::map<BRICK_TYPE,char> brickTypeMap;

	brickTypeMap[M] = 'M';
	brickTypeMap[H] = 'H';
	brickTypeMap[I] = 'I';
	brickTypeMap[S] = 'S';
	brickTypeMap[EMPTY] = ' ';


	int i = 0;

	int red = 0;
	int stupac = 0;
	std::cout << "\nSTART";
	std::cout << brickAlignment;
	std::cout << "FIN\n";

	for (char& c : brickAlignment) {
		switch (c) {
		case 'M':
			stupac++;
			
			break;
		case 'H':
			stupac++;
			
			break;
		case 'I':
			stupac++;
	
			break;
		case 'S':
			stupac++;

			break;
		case ' ':
			
			
			break;
		case '\n':

			red++;
			stupac = 0;
			
			
			break;
		}
		
		if(c!=' ' && c!= '\n')
			std::cout << "\n" << stupac-1 << " "<< red << " "  << c;

		this->gridSizeU = 400;

		if (c != ' ' && c != '\n')
			this->map[stupac-1][red][0] = new Brick(
				stupac, red,
				200,
				this->tileTextureSheet,
				sf::IntRect(0, 0, this->gridSizeU, this->gridSizeU/2),
				true,
				0);


		i++;
	}

	
	
	
}

BrickMap::~BrickMap()
{
	this->clear();
}

//Accessors
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

void BrickMap::addTile(const unsigned x, const unsigned y, const unsigned z, const sf::IntRect& tex_rect, const bool& collision, const bool& type)
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
			this->map[x][y][z] = new Brick(x, y, this->gridSizeF, this->tileTextureSheet, tex_rect, collision, type);
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
			this->map[x][y][z] = new Brick(
				x, y,
				gridSizeF,
				this->tileTextureSheet,
				sf::IntRect(trX, trY, this->gridSizeU, this->gridSizeU),
				collision,
				type);
			std::cout << "LOADED " << x << " " << y << "\n";
		}

	}
	else
	{
		std::cout << "ERROR:TILEMAP:COULD_LOAD_FROM_FILE::FILENAME:" << fileName << "\n";
	}

	in_file.close();
}