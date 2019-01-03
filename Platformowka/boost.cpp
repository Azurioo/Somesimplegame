#include "boost.h"
#include <time.h> 
#include <SFML/Graphics.hpp>
#include <windows.h>

void boost::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(this->shape_, states);
}

boost::boost(float x, float y)
{
	srand(clock()); 
	auto i = rand() % (boost_sum_+1);
	if (i <= this->multifire_boost_chance_) boost_ = "multifire"; 
	else if (i <= this->multifire_boost_chance_ + size_boost_chance_) boost_ = "size"; 
	else if (i <= this->multifire_boost_chance_ + size_boost_chance_ + speed_boost_chance_) boost_ = "speed"; 
	else boost_ = "wallhack"; shape_.setPosition(x, y); 
	shape_.setFillColor(sf::Color::Green); shape_.setSize({ this->shape_size_, this->shape_size_ });
} 

float boost::left() const
{
	return this->shape_.getPosition().x;
} 

float boost::right() const 
{ 
	return this->shape_.getPosition().x + shape_.getSize().x; 
} 

float boost::top() const
{
	return this->shape_.getPosition().y;
} 

float boost::bottom() const
{
	return this->shape_.getPosition().y + shape_.getSize().y;
} 

std::string boost::what_boost() const
{
	return this->boost_;
} 