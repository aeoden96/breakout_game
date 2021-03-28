#include "Brick.h"



Brick::Brick(unsigned grid_x, unsigned grid_y, float gridSizeF, const sf::Texture& texture, const sf::IntRect& tex_rect,
	bool collision, short type)
{
	this->shape.setSize(sf::Vector2f(gridSizeF, gridSizeF));
	this->shape.setFillColor(sf::Color::White);
	this->shape.setPosition(static_cast<float>(grid_x) * gridSizeF, static_cast <float>(grid_y) * gridSizeF);
	//this->shape.setOutlineColor(sf::Color::Black);
	//this->shape.setOutlineThickness(1.f);
	this->shape.setTexture(&texture);
	this->shape.setTextureRect(tex_rect);

	this->collision = collision;
	this->type = type;

}

Brick::Brick()
{
	this->collision = false;
	this->type = 0;
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

void Brick::update()
{

}

void Brick::render(sf::RenderTarget& target)
{
	target.draw(this->shape);
}