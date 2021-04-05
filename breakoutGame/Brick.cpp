#include "Brick.h"



Brick::Brick(unsigned grid_x,
	unsigned grid_y, 
	float gridSizeF_x, 
	float gridSizeF_y, 
	const sf::Texture& texture, 
	const sf::IntRect& tex_rect,
	bool collision, 
	short type, 
	char id,
	int hitsToCrack)
{
	//this->shape.setScale(0.25f,0.25f);
	this->shape.setSize(sf::Vector2f(gridSizeF_x, gridSizeF_y));
	
	this->shape.setPosition(static_cast<float>(grid_x) * (gridSizeF_x+3), static_cast <float>(grid_y) * (gridSizeF_y+3)+100);


	this->shape.setTexture(&texture);
	this->shape.setTextureRect(tex_rect);
	this->isHit = false;
	this->collision = collision;
	this->type = type;
	this->brickType = id;
	this->hitsToCrack = hitsToCrack;
	//this->hitsToCrack = 2;

}
void Brick::crackIt(int posX, int posY, int sizeX, int sizeY) {
	if (hitsToCrack == 1) {
		this->hit();
	}
	if(hitsToCrack>0)
		this->shape.setTextureRect(sf::IntRect(posX, posY, sizeX, sizeY));
		hitsToCrack--;
}
Brick::Brick()
{
	this->collision = false;
	this->type = 0;
	this->isHit = false;
	this->brickType = brickTypeClass::UNDEF;

	
}

sf::FloatRect Brick::returnPosition() {
	if(!this->isHit)
		return this->shape.getGlobalBounds();

	return sf::FloatRect();
}

void Brick::hit()
{
	if (!this->isHit)
	{
		this->isHit = true;
	}

	if (collision) {
		collision = false;
	}
}


Brick::~Brick()
{
}





//Functions
const std::string Brick::getAsString() const
{
	std::stringstream ss;

	ss << this->shape.getTextureRect().left << " " << this->shape.getTextureRect().top << " " << this->collision
		<< " " << this->type;

	return ss.str();

}

char Brick::getBrickType()
{
	return this->brickType;
}

int Brick::getCrackNum()
{
	return this->hitsToCrack;
}

void Brick::update()
{

}

void Brick::render(sf::RenderTarget& target)
{
	if(!isHit)
		target.draw(this->shape);
}