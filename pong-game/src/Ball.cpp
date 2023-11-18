#include "Ball.h"

game::Ball::Ball() {
	shape.setSize(sf::Vector2f(40, 40));
}

void game::Ball::setPosition(float x, float y) {
	pos.x = x;
	pos.y = y;
	shape.setPosition(pos);
}

void game::Ball::update(const sf::Time& dt) {
	pos.x += speedX * speedModifier * dt.asSeconds();
	pos.y += speedY * speedModifier * dt.asSeconds();
	shape.setPosition(pos);
}


