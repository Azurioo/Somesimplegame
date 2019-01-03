#pragma once
#include <SFML/Graphics.hpp>

class player :public sf::Drawable
{
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	bool destoryed{ false };
	sf::RectangleShape shape_;
	const float shape_width_{ 25 };
	const float shape_height_{ 25 };
	const float shape_velocity_{ 2.0f };
	const float shape_boosted_velocity_{ 4.0f };
	sf::Keyboard::Key shape_left_;
	sf::Keyboard::Key shape_right_;
	sf::Keyboard::Key shape_up_;
	sf::Keyboard::Key shape_down_;
	std::string shape_face_direction_ = "up";
	int gun_cooldown_{ 1 };

	struct gun
	{
		float x;
		float y;
	};


	sf::Vector2f velocity_{ shape_velocity_ , shape_velocity_ };

public:
	~player() = default;
	player() = delete;
	player(float t_x, float t_y, sf::Color color, sf::Keyboard::Key left, sf::Keyboard::Key right, sf::Keyboard::Key up, sf::Keyboard::Key down);

	void update();
	float left() const;
	float right() const;
	float top() const;
	float bottom() const;
	void block_left();
	void block_right();
	void block_bottom();
	void block_top();
	sf::Keyboard::Key key_left() const;
	sf::Keyboard::Key key_right() const;
	sf::Keyboard::Key key_up() const;
	sf::Keyboard::Key key_down() const;
	gun gun_postion() const;
	int cooldown_time() const;
	std::string bullet_direction() const;
	void destroy();
};

