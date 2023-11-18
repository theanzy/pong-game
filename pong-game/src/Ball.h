#pragma once
#include <SFML/Graphics.hpp>
namespace game {
	class Ball {
	public:
		sf::Vector2f pos;
		sf::RectangleShape shape;
		float speedX = 200;
		float speedY = -200;
		float speedModifier = 2.5f;
	public:
		Ball();
		void setPosition(float x, float y);
		void update(const sf::Time& dt);
	};

}