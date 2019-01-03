#include "player.h"
#include "wall.h"
#include <SFML/Graphics.hpp>

void player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(this->shape_, states);
}

player::player(float t_x, float t_y, sf::Color color, sf::Keyboard::Key left, sf::Keyboard::Key right, sf::Keyboard::Key up, sf::Keyboard::Key down)
{
	shape_.setPosition(t_x, t_y);
	shape_.setSize({ this->shape_width_,this->shape_height_ });
	shape_.setFillColor(color);
	shape_.setOrigin(this->shape_width_/2, this->shape_height_/2);
	shape_left_ = left;
	shape_right_ = right;
	shape_up_ = up;
	shape_down_ = down;
}

void player::update()
{
	if(destoryed)
	{
		this->shape_.setFillColor(sf::Color::White);
	}

	this->shape_.move(this->velocity_);

	if (sf::Keyboard::isKeyPressed(shape_left_))
	{
		velocity_.x = -shape_velocity_;
		if (sf::Keyboard::isKeyPressed(shape_up_))
		{
			this->shape_face_direction_ = "left/up";
			velocity_.x = -shape_velocity_ / 1.72f;
			velocity_.y = -shape_velocity_ / 1.72f;
		}
		else if (sf::Keyboard::isKeyPressed(shape_down_))
		{
			shape_face_direction_ = "down/left";
			velocity_.x = -shape_velocity_ / 1.72f;
			velocity_.y = shape_velocity_ / 1.72f;
		}
		else
		{
			this->shape_face_direction_ = "left";
		}
	}
	else if (sf::Keyboard::isKeyPressed(shape_right_))
	{
		velocity_.x = shape_velocity_;
		if (sf::Keyboard::isKeyPressed(shape_down_))
		{
			this->shape_face_direction_ = "right/down";
			velocity_.x = shape_velocity_ / 1.72f;
			velocity_.y = shape_velocity_ / 1.72f;
		}
		else if (sf::Keyboard::isKeyPressed(shape_up_))
		{
			shape_face_direction_ = "up/right";
			velocity_.x = shape_velocity_ / 1.72f;
			velocity_.y = -shape_velocity_ / 1.72f;
		}
		else
		{
			shape_face_direction_ = "right";
		}
	}
	else
	{
		velocity_.x = 0;
	}


	if (sf::Keyboard::isKeyPressed(shape_up_))
	{
		velocity_.y = -shape_velocity_;
		if (sf::Keyboard::isKeyPressed(shape_right_))
		{
			shape_face_direction_ = "up/right";
			velocity_.x = shape_velocity_ / 1.72f;
			velocity_.y = -shape_velocity_ / 1.72f;
		}
		else if (sf::Keyboard::isKeyPressed(shape_left_))
		{
			shape_face_direction_ = "left/up";
			velocity_.x = -shape_velocity_ / 1.72f;
			velocity_.y = -shape_velocity_ / 1.72f;
		}
		else
		{
			shape_face_direction_ = "up";
		}
	}
	else if (sf::Keyboard::isKeyPressed(shape_down_))
	{
		velocity_.y = shape_velocity_;
		if (sf::Keyboard::isKeyPressed(shape_left_))
		{
			this->shape_face_direction_ = "down/left";
			velocity_.x = -shape_velocity_ / 1.72f;
			velocity_.y = shape_velocity_ / 1.72f;
		}
		else if (sf::Keyboard::isKeyPressed(shape_right_))
		{
			shape_face_direction_ = "right/down";
			velocity_.x = shape_velocity_ / 1.72f;
			velocity_.y = shape_velocity_ / 1.72f;
		}
		else
		{
			this->shape_face_direction_ = "down";
		}
	}
	else
	{
		velocity_.y = 0;
	}
}

float player::left() const
{
	return this->shape_.getPosition().x - shape_.getSize().x/2.f;
}

float player::right() const
{
	return this->shape_.getPosition().x + shape_.getSize().x/2.f;
}

float player::top() const
{
	return this->shape_.getPosition().y - shape_.getSize().y/2.f;
}

float player::bottom() const
{
	return this->shape_.getPosition().y + shape_.getSize().y/2.f;
}

void player::block_left()
{
	velocity_.x = 0;
}

void player::block_right()
{
	velocity_.x = 0;
}

void player::block_bottom()
{
	velocity_.y = 0;
}

void player::block_top()
{
	velocity_.y = 0;
}

sf::Keyboard::Key player::key_left() const
{
	return this->shape_left_;
}

sf::Keyboard::Key player::key_right() const
{
	return this->shape_right_;
}

sf::Keyboard::Key player::key_up() const
{
	return this->shape_up_;
}

sf::Keyboard::Key player::key_down() const
{
	return this->shape_down_;
}

player::gun player::gun_postion() const
{
	gun gun = {};
	if(this->shape_face_direction_ == "up")
	{
		gun.x = this->shape_.getPosition().x;
		gun.y = this->shape_.getPosition().y - shape_.getSize().y / 2.f - 2.f;
	}
	else if (this->shape_face_direction_ == "left")
	{
		gun.x = this->shape_.getPosition().x - shape_.getSize().x / 2.f - 2.f;
		gun.y = this->shape_.getPosition().y;
	}
	else if (this->shape_face_direction_ == "right")
	{
		gun.x = this->shape_.getPosition().x + shape_.getSize().x / 2.f + 2.f;
		gun.y = this->shape_.getPosition().y;
	}
	else if (this->shape_face_direction_ == "down")
	{
		gun.x = this->shape_.getPosition().x;
		gun.y = this->shape_.getPosition().y + shape_.getSize().y / 2.f + 2.f;
	}
	else if (this->shape_face_direction_ == "up/right")
	{
		gun.x = this->shape_.getPosition().x + shape_.getSize().x / 2.f + 3.f;
		gun.y = this->shape_.getPosition().y - shape_.getSize().y / 2.f - 3.f;
	}
	else if (this->shape_face_direction_ == "right/down")
	{
		gun.x = this->shape_.getPosition().x + shape_.getSize().x / 2.f + 3.f;
		gun.y = this->shape_.getPosition().y + shape_.getSize().y / 2.f + 3.f;
	}
	else if (this->shape_face_direction_ == "down/left")
	{
		gun.x = this->shape_.getPosition().x - (shape_.getSize().x / 2.f) - 3.f;
		gun.y = this->shape_.getPosition().y + (shape_.getSize().y / 2.f) + 3.f;
	}
	else if (this->shape_face_direction_ == "left/up")
	{
		gun.x = this->shape_.getPosition().x - (shape_.getSize().x / 2.f) - 3.f;
		gun.y = this->shape_.getPosition().y - (shape_.getSize().y / 2.f) - 3.f;
	}
	return gun;
}

int player::cooldown_time() const
{
	return this->gun_cooldown_;
}

std::string player::bullet_direction() const
{
	return this->shape_face_direction_;
}

void player::destroy()
{
	this->destoryed = true;
}
