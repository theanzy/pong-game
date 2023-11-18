#include "Paddle.h"
#include <fmt/core.h>
game::Paddle::Paddle() {
	pos.x = 0;
	pos.y = 0;
	shape.setPosition(pos);
	shape.setSize(sf::Vector2f(25, 200));
}

void game::Paddle::setPosition(float x, float y) {
	pos.x = x;
	pos.y = y;
	shape.setPosition(pos);
}

void game::Paddle::update(const sf::Time& dt) {
	if (movingDown) {
		pos.y += speedY * dt.asSeconds();
	}

	if (movingUp) {
		pos.y -= speedY * dt.asSeconds();
	}

	shape.setPosition(pos);
}

