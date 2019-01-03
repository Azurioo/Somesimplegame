#include "wall.h"
#include <SFML/Graphics.hpp>


void wall::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(this->shape_, states);
}

wall::wall(float t_x, float t_y, float t_width, float t_height)
{
	shape_.setPosition(t_x, t_y);
	shape_.setFillColor(sf::Color::Black);
	shape_.setSize({ t_width, t_height });
}

float wall::left() const
{
	return this->shape_.getPosition().x;
}

float wall::right() const
{
	return this->shape_.getPosition().x + shape_.getSize().x;
}

float wall::top() const
{
	return this->shape_.getPosition().y;
}

float wall::bottom() const
{
	return this->shape_.getPosition().y + shape_.getSize().y;
}