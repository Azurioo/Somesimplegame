#pragma once
#include <SFML/Graphics.hpp>
class laser :public sf::Drawable
{
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	sf::RectangleShape shape_;
	const float shape_width_{ 25 };
	const float shape_height_{ 25 };

public:
	laser() = delete;
	~laser() = default;
	laser(float x, float y, std::string direction);
};

