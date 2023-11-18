#pragma once
#include <SFML/Graphics.hpp>
namespace game {
	class Paddle {
	public:
		sf::Vector2f pos;
		sf::RectangleShape shape;
		bool movingUp = false;
		bool movingDown = false;
		float speedY = 350.0f;
	private:
	public:
		Paddle();
		void setPosition(float x, float y);
		void update(const sf::Time& dt);
	};
}


