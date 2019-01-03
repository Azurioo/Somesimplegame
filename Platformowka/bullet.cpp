#include "bullet.h"
#include <SFML/Graphics.hpp>

void bullet::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(this->shape_, states);
}

bullet::bullet(float t_x, float t_y, bool speed_boost, bool wall_hack_boost, std::string direction)
{
	shape_.setPosition(t_x, t_y);
	shape_.setOrigin(this->shape_radious_, this->shape_radious_);
	shape_.setRadius(this->shape_radious_);
	shape_.setFillColor(sf::Color::Black);

	if (speed_boost)
		this->shape_velocity_ = 7.0f;
	else
		this->shape_velocity_ = 3.5f;

	this->wall_hack_ = wall_hack_boost;
	this->shape_direction_ = direction;
}

void bullet::update()
{
	if(this->bullet_durability_ <= 0)
		this->destoryed_ = true;
	else if (this->shape_direction_ == "up")
	{
		velocity_.y = -shape_velocity_;
		velocity_.x = 0.f;
	}
	else if (this->shape_direction_ == "down")
	{
		velocity_.y = shape_velocity_;
		velocity_.x = 0.f;
	}
	else if (this->shape_direction_ == "left")
	{
		velocity_.x = -shape_velocity_;
		velocity_.y = 0.f;
	}
	else if (this->shape_direction_ == "right")
	{
		velocity_.x = shape_velocity_;
		velocity_.y = 0.f;
	}
	else if (this->shape_direction_ == "up/right")
	{
		velocity_.y = -shape_velocity_/1.72f;
		velocity_.x = shape_velocity_ / 1.72f;
	}
	else if (this->shape_direction_ == "right/down")
	{
		velocity_.y = shape_velocity_ / 1.72f;
		velocity_.x = shape_velocity_ / 1.72f;
	}
	else if (this->shape_direction_ == "down/left")
	{
		velocity_.x = -shape_velocity_ / 1.72f;
		velocity_.y = shape_velocity_ / 1.72f;
	}
	else if (this->shape_direction_ == "left/up")
	{
		velocity_.x = -shape_velocity_ / 1.72f;
		velocity_.y = -shape_velocity_ / 1.72f;
	}
	this->shape_.move(this->velocity_);
}

float bullet::left() const
{
	return this->shape_.getPosition().x - shape_.getRadius();
}

float bullet::right() const
{
	return this->shape_.getPosition().x + shape_.getRadius();
}

float bullet::top() const
{
	return shape_.getPosition().y - shape_.getRadius();
}

float bullet::bottom() const
{
	return this->shape_.getPosition().y + this->shape_.getRadius();
}

bool bullet::is_destoryed() const
{
	return this->destoryed_;
}

void bullet::destory()
{
	this->destoryed_ = true;
}

void bullet::bounce_right()
{
	this->bullet_durability_--;
	this->velocity_.x = shape_velocity_;
	if (this->shape_direction_ == "down/left")
		this->shape_direction_ = "right/down";
	else if (this->shape_direction_ == "left/up")
		this->shape_direction_ = "up/right";
	else
		this->shape_direction_ = "right";
	this->update();
}

void bullet::bounce_left()
{
	this->bullet_durability_--;
	this->velocity_.x = -shape_velocity_;
	if (this->shape_direction_ == "up/right")
		this->shape_direction_ = "left/up";
	else if (this->shape_direction_ == "right/down")
		this->shape_direction_ = "down/left";
	else
		this->shape_direction_ = "left";
	this->update();
}

void bullet::bounce_up()
{
	this->bullet_durability_--;
	this->velocity_.y = -shape_velocity_;
	if (this->shape_direction_ == "down/left")
		this->shape_direction_ = "left/up";
	else if (this->shape_direction_ == "right/down")
		this->shape_direction_ = "up/right";
	else
		this->shape_direction_ = "up";
	this->update();
}

void bullet::bounce_down()
{
	this->bullet_durability_--;
	this->velocity_.y = shape_velocity_;
	if (this->shape_direction_ == "up/right")
		this->shape_direction_ = "right/down";
	else if (this->shape_direction_ == "left/up")
		this->shape_direction_ = "down/left";
	else
		this->shape_direction_ = "down";
	this->update();
}

bool bullet::have_wallhack() const
{
	return this->wall_hack_;
}