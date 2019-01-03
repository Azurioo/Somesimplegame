#pragma once
#include <SFML/Graphics.hpp>

class boost :public sf::Drawable
{
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	sf::RectangleShape shape_;
	const float shape_size_{ 10 };
	std::string boost_;
	const int size_boost_chance_{ 0 };
	const int speed_boost_chance_{ 40 };
	const int wallhack_boost_chance_{ 40 };
	const int multifire_boost_chance_{ 30 };
	const int boost_sum_ = size_boost_chance_ + speed_boost_chance_ + wallhack_boost_chance_ + multifire_boost_chance_;

public:
	boost() = delete;
	~boost() = default;

	boost(float t_x, float t_y);

	float left() const;
	float right() const;
	float top() const;
	float bottom() const;

	std::string what_boost() const;
};