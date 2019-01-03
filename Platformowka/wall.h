#pragma once
#include <SFML/Graphics.hpp>

class wall: public sf::Drawable
{
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	sf::RectangleShape shape_;

public:
	wall() = delete;
	~wall() = default;
	wall(float t_x, float t_y, float t_width, float t_height);

	float left() const;
	float right() const;
	float top() const;
	float bottom() const;
};