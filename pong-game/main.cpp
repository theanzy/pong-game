#include <fmt/core.h>
#include <SFML/Graphics.hpp>
#include "src/Paddle.h"


const int WIDTH = 1920;
const int HEIGHT = 1080;
int main(int argc, char* argv[]) {
	using namespace game;

	sf::VideoMode vm(WIDTH, HEIGHT);
	sf::RenderWindow window(vm, "Pong", sf::Style::Default);

	sf::Font font;
	if (font.loadFromFile("assets/fonts/kirbyss.ttf") == false) {
		return 1;
	}

	int score = 0;
	sf::Text scoreText;
	scoreText.setFont(font);
	scoreText.setFillColor(sf::Color::White);
	scoreText.setString("Score: 0");
	scoreText.setPosition(20, 20);
	scoreText.setCharacterSize(28);

	// offset
	const float OFFSET_TOP = 50;
	const float OFFSET_X = 20;

	Paddle paddle;
	paddle.setPosition(WIDTH - paddle.shape.getLocalBounds().width - OFFSET_X, HEIGHT / 2.0f - paddle.shape.getLocalBounds().height / 2.0f);

	// loop
	sf::Clock clock;
	sf::Event event;
	while (window.isOpen()) {
		const auto dt = clock.restart();
		// events
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
			window.close();
			continue;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			paddle.movingUp = true;
		}
		else {
			paddle.movingUp = false;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			paddle.movingDown = true;
		}
		else {
			paddle.movingDown = false;
		}

		// update elements
		
		if (paddle.pos.y <= OFFSET_TOP) {
			paddle.movingUp = false;
		}
		else if (paddle.pos.y + paddle.shape.getLocalBounds().height >= HEIGHT) {
			paddle.movingDown = false;
		}

		paddle.update(dt);

		// draw
		window.clear();

		//  draw elements
		window.draw(scoreText);
		window.draw(paddle.shape);

		window.display();

	}
	return 0;
}

