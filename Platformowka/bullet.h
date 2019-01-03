#pragma once
#include <SFML/Graphics.hpp>

class bullet: public sf::Drawable
{

	sf::CircleShape shape_;
	float shape_radious_{ 3.0f };
	float shape_velocity_{ 0 };
	std::string shape_direction_;
	bool destoryed_{ false };
	bool wall_hack_{ false };
	int bullet_durability_ = 7;

	sf::Vector2f velocity_{ shape_velocity_, shape_velocity_ };

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
	bullet() = delete;
	~bullet() = default;
	bullet(float t_x, float t_y,bool speed_boost, bool wall_hack_boost, std::string direction);
	
	void update();
	float left() const;
	float right() const;
	float top() const;
	float bottom() const;
	bool is_destoryed() const;
	void destory();
	void bounce_right();
	void bounce_left();
	void bounce_up();
	void bounce_down();
	bool have_wallhack() const;
};