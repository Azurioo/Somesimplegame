#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <time.h>
#include "wall.h"
#include "player.h"
#include "bullet.h"
#include "boost.h"
#include <windows.h>

using namespace sf;
using namespace std;

struct player_boosts
{
	int speed = 0;
	int wall_hack = 0;
	int multi_fire = 0;
	int laser = 0;
};

static int boost_count = 5;
player_boosts player1;
player_boosts player2;

template <class T1, class T2> bool isIntersecting(T1& a, T2& b)
{
	return a.right() >= b.left() && a.left() <= b.right() && a.bottom() >= b.top() && a.top() <= b.bottom();
}

bool walls_collisions(wall& wall, player& player)
{
	if (!isIntersecting(wall, player)) return false;

	float overlapLeft{ player.right() - wall.left() };
	float overlapRight{ wall.right() - player.left() };

	float overlapTop{ player.bottom() - wall.top() };
	float overlapBottom{ wall.bottom() - player.top() };

	bool playerFromLeft(abs(overlapLeft) < abs(overlapRight));
	bool playerFromTop(abs(overlapTop) < abs(overlapBottom));

	float minOverlapX{ playerFromLeft ? overlapLeft : overlapRight };
	float minOverlapY{ playerFromTop ? overlapTop : overlapBottom };

	if(abs(minOverlapX) < abs(minOverlapY))
	{
		if (playerFromLeft && Keyboard::isKeyPressed(player.key_right()))
			player.block_right();
		else if (!playerFromLeft && Keyboard::isKeyPressed(player.key_left()))
			player.block_left();
	}
	else
	{
		if (playerFromTop && Keyboard::isKeyPressed(player.key_down()))
			player.block_bottom();
		else if (!playerFromTop && Keyboard::isKeyPressed(player.key_up()))
			player.block_top();
	}
	return true;
}

bool bullet_collision(wall& wall, bullet& bullet)
{
	if (!isIntersecting(wall, bullet)) return false;

	if (bullet.have_wallhack())
	{
		if (bullet.left() > 790.0f || bullet.right() < 10.0f)
			bullet.destory();
		else if (bullet.top() > 590.0f || bullet.bottom() < 10.0f)
			bullet.destory();
		return false;
	}
	float overlapLeft{ bullet.right() - wall.left() };
	float overlapRight{ wall.right() - bullet.left() };

	float overlapTop{ bullet.bottom() - wall.top() };
	float overlapBottom{ wall.bottom() - bullet.top() };

	bool bulletFromLeft(abs(overlapLeft) < abs(overlapRight));
	bool bulletFromTop(abs(overlapTop) < abs(overlapBottom));

	float minOverlapX{ bulletFromLeft ? overlapLeft : overlapRight };
	float minOverlapY{ bulletFromTop ? overlapTop : overlapBottom };

	if (abs(minOverlapX) < abs(minOverlapY))
		bulletFromLeft ? bullet.bounce_left() : bullet.bounce_right();
	else
		bulletFromTop ? bullet.bounce_up() : bullet.bounce_down();
	return true;
}

bool boost_collision(boost& boosts, player& player, const int i, vector<boost> &boost)
{
	if (!isIntersecting(boosts, player)) return false;

	else if (boosts.what_boost() == "speed")
	{
		if (i == 0)
			player1.speed = boost_count;
		else
			player2.speed = boost_count;
	}
	else if (boosts.what_boost() == "wallhack")
	{
		if (i == 0)
			player1.wall_hack = boost_count;
		else
			player2.wall_hack = boost_count;
	}
	else if (boosts.what_boost() == "multifire")
	{
		if (i == 0)
			player1.multi_fire = boost_count - 1;
		else
			player2.multi_fire = boost_count - 1;
	}
	boost.pop_back();
	return true;
}

int main()
{
	RenderWindow window(VideoMode(800, 800), "Gra");
	window.setFramerateLimit(60);

	Event event;

	vector<wall> walls;
	vector<player> players;
	vector<boost> boosts;
	vector<bullet> bullets;

	//sciany
	{
		//ramka
		walls.emplace_back(0, 0, 800, 25);
		walls.emplace_back(0, 0, 25, 600);
		walls.emplace_back(0, 575, 800, 25);
		walls.emplace_back(775, 0, 25, 600);
		//radomowki
		walls.emplace_back(0, 75, 125, 25);
		walls.emplace_back(100, 162.5, 25, 200);
		walls.emplace_back(100, 362.5, 300, 25);
		walls.emplace_back(100, 437.5, 25, 95);
		walls.emplace_back(100, 437.5, 150, 25);
		walls.emplace_back(190, 510, 25, 90);
		walls.emplace_back(325, 437.5, 375, 25);
		walls.emplace_back(465, 362.6, 25, 75);
		walls.emplace_back(600, 332.6, 25, 120);
		walls.emplace_back(685, 332.6, 100, 25);
		walls.emplace_back(532.5, 132.5, 25, 255);
		walls.emplace_back(532.5, 250, 180, 25);
		walls.emplace_back(200, 265, 288.5, 25);
		walls.emplace_back(200, 0, 25, 200);
		walls.emplace_back(200, 90, 100, 25);
		walls.emplace_back(350, 90, 100, 25);
		walls.emplace_back(450, 0, 25, 200);
		walls.emplace_back(275, 175, 175, 25);
		walls.emplace_back(532.5, 65, 177.5, 25);
		walls.emplace_back(687.5, 132.5, 25, 120);
		walls.emplace_back(610, 65, 25, 130);

		//kulki
		walls.emplace_back(470, 510, 40, 40);
		walls.emplace_back(590, 490, 40, 40);
		walls.emplace_back(710, 510, 40, 40);
		walls.emplace_back(350, 490, 40, 40);
	}


	struct text
	{
		sf::String score;
		sf::String player_1;
		sf::String player_2;
	};
	text text;
	text.score;

	

	bool restart = false;
	int player1_score = 0;
	int player2_score = 0;
	bool menu = false;

	clock_t player1_cooldown = 0;
	clock_t player2_cooldown = 0;

	bool ready;
	do
	{
		ready = true;
		srand(time(nullptr));
		int x = rand() % 750 + 25;
		srand(clock());
		int y = rand() % 550 + 25;
		players.emplace_back(x, y, Color::Red, sf::Keyboard::Key::Left, sf::Keyboard::Key::Right, sf::Keyboard::Key::Up, sf::Keyboard::Key::Down);
		for (auto& wall : walls)
		{
			if (isIntersecting(wall, players[0]))
			{
				players.pop_back();
				ready = false;
				break;
			}
		}
	} while (!ready);
	ready = false;
	do
	{
		ready = true;
		srand(time(nullptr)+1000);
		int x = rand() % 750 + 25;
		srand(clock()+1000);
		int y = rand() % 550 + 25;
		players.emplace_back(x, y, Color::Blue, sf::Keyboard::Key::A, sf::Keyboard::Key::D, sf::Keyboard::Key::W, sf::Keyboard::Key::S);
		for (auto& wall : walls)
		{
			if (isIntersecting(wall, players[1]) || isIntersecting(players[0], players[1]))
			{
				players.pop_back();
				ready = false;
				break;
			}
		}
	} while (!ready);

	clock_t boost_cooldown = clock() + 10 * CLOCKS_PER_SEC;

	while (window.isOpen())
	{
		window.clear(Color::White);

		while(menu)
		{
			while (window.pollEvent(event))
			{
				if (event.type == Event::Closed)
				{
					window.close();
				}
				if (event.type == Event::KeyPressed && event.key.code == Keyboard::Return)
				{
					menu = false;
				}
			}
		}

		if(restart)
		{
			players.clear();
			bullets.clear();
			boosts.clear();
			{
				player1.multi_fire = 0;
				player1.laser = 0;
				player1.speed = 0;
				player1.wall_hack = 0;
				player2.multi_fire = 0;
				player2.laser = 0;
				player2.speed = 0;
				player2.wall_hack = 0;
			}
			do
			{
				ready = true;
				srand(time(nullptr));
				int x = rand() % 750 + 25;
				srand(clock());
				int y = rand() % 550 + 25;
				players.emplace_back(x, y, Color::Red, sf::Keyboard::Key::Left, sf::Keyboard::Key::Right, sf::Keyboard::Key::Up, sf::Keyboard::Key::Down);
				for (auto& wall : walls)
				{
					if (isIntersecting(wall, players[0]))
					{
						players.pop_back();
						ready = false;
						break;
					}
				}
			} while (!ready);
			ready = false;
			do
			{
				ready = true;
				srand(time(nullptr) + 1000);
				int x = rand() % 750 + 25;
				srand(clock() + 1000);
				int y = rand() % 550 + 25;
				players.emplace_back(x, y, Color::Blue, sf::Keyboard::Key::A, sf::Keyboard::Key::D, sf::Keyboard::Key::W, sf::Keyboard::Key::S);
				for (auto& wall : walls)
				{
					if (isIntersecting(wall, players[1]) || isIntersecting(players[0], players[1]))
					{
						players.pop_back();
						ready = false;
						break;
					}
				}
			} while (!ready);
			restart = false;
		}
		
		if(boost_cooldown < clock() && boosts.begin() == boosts.end())
		{
			do
			{
				ready = true;
				srand(time(nullptr));
				int x = rand() % 750 + 25;
				srand(clock());
				int y = rand() % 550 + 25;
				boosts.emplace_back(x, y);
				for (auto& wall : walls)
				{
					for (auto& boost : boosts)
					{
						if (isIntersecting(wall, boost))
						{
							boosts.pop_back();
							ready = false;
							break;
						}
					}
				}
			} while (!ready);
			boost_cooldown = boost_cooldown = clock() + 15 * CLOCKS_PER_SEC;
		}
		
		//klawiatura
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();
			}

			if( event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
			{
				menu = true;
			}

			if (event.type == Event::KeyPressed && event.key.code == Keyboard::RShift && player1_cooldown < clock())
			{
				bool speed = false, size = false, wallhack = false, multifire = false;

				if (player1.speed > 0)
				{
					player1.speed--;
					speed = true;
				}
				if (player1.wall_hack > 0)
				{
					player1.wall_hack--;
					wallhack = true;
				}
				if (player1.multi_fire > 0)
				{
					player1.multi_fire--;
					multifire = true;
					bullets.emplace_back(players[0].gun_postion().x, players[0].gun_postion().y, speed, wallhack, players[0].bullet_direction());
					break;
				}
				bullets.emplace_back(players[0].gun_postion().x, players[0].gun_postion().y, speed, wallhack, players[0].bullet_direction());
				player1_cooldown = clock() + players[0].cooldown_time() * CLOCKS_PER_SEC;
			}

			if (event.type == Event::KeyPressed && event.key.code == Keyboard::LShift && player2_cooldown < clock())
			{
				bool speed = false, size = false, wallhack = false, multifire = false;

				if (player2.speed > 0)
				{
					player2.speed--;
					speed = true;
				}
				if (player2.wall_hack > 0)
				{
					player2.wall_hack--;
					wallhack = true;
				}
				if (player2.multi_fire > 0)
				{
					player2.multi_fire--;
					multifire = true;
					bullets.emplace_back(players[1].gun_postion().x, players[1].gun_postion().y, speed, wallhack, players[1].bullet_direction());
					break;
				}
				bullets.emplace_back(players[1].gun_postion().x, players[1].gun_postion().y, speed, wallhack, players[1].bullet_direction());
				player2_cooldown = clock() + players[1].cooldown_time() * CLOCKS_PER_SEC;
			}
		}

		//aktualizacje
		{
			players[0].update();
			players[1].update();
			for (auto& bullet : bullets)
				bullet.update();
		}

		//kolizje
		{
			for (auto& wall : walls)
			{
				for (auto& bullet : bullets)
					bullet_collision(wall, bullet);
			}

			for (auto& wall : walls)
				walls_collisions(wall, players[0]);

			for (auto& wall : walls)
				walls_collisions(wall, players[1]);

			for (auto& boost : boosts)
			{
				boost_collision(boost, players[0], 0, boosts);
				boost_collision(boost, players[1], 1, boosts);
			}

			auto iterator_bullet = remove_if(begin(bullets), end(bullets), [](bullet& bullet) {return bullet.is_destoryed(); });
			bullets.erase(iterator_bullet, end(bullets));

			for (auto& bullet : bullets)
			{
				if (isIntersecting(players[0], bullet))
				{
					players[0].destroy();
					player2_score++;
					restart = true;
				}
				if (isIntersecting(players[1], bullet))
				{
					players[1].destroy();
					player1_score++;
					restart = true;
				}
			}
		}

		//rysowanie
		{
			for (auto& wall : walls)
				window.draw(wall);

			for (auto& bullet : bullets)
				window.draw(bullet);

			for (auto& boost : boosts)
				window.draw(boost);

			window.draw(players[1]);
			window.draw(players[0]);
			window.display();
		}
	}
	return 0;
}