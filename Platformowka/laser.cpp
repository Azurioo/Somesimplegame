#include "laser.h"

void laser::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(this->shape_, states);
}

laser::laser(float x, float y, std::string direction)
{
	shape_.setPosition(x,y);
	shape_.setSize({ this->shape_width_,this->shape_height_ });
	shape_.setFillColor(sf::Color::Red);
	if(direction == "up" || direction == "down")
	shape_.setOrigin(this->shape_width_ / 2, this->shape_height_ / 2);
}
