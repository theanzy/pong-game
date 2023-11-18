#include <fmt/core.h>
#include <SFML/Graphics.hpp>
#include "Paddle.h"
#include "Ball.h"


const int WIDTH = 1920;
const int HEIGHT = 1080;

bool rectsAreColliding(const sf::FloatRect& a, const sf::FloatRect& b);

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
	paddle.setPosition(WIDTH - paddle.shape.getLocalBounds().width - OFFSET_X, HEIGHT / 2.0f + OFFSET_TOP - paddle.shape.getLocalBounds().height / 2.0f);

	Paddle botPaddle;
	botPaddle.setPosition(OFFSET_X, HEIGHT / 2.0f + OFFSET_TOP - botPaddle.shape.getLocalBounds().height / 2.0f);
	botPaddle.shape.setFillColor(sf::Color::Red);


	Ball ball;
	ball.setPosition(WIDTH / 2.0f - ball.shape.getLocalBounds().width / 2, HEIGHT / 2.0f + OFFSET_TOP - ball.shape.getLocalBounds().height / 2.0f);

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

		// move bot paddle
		if (botPaddle.pos.y + botPaddle.shape.getLocalBounds().height / 2.0f > ball.pos.y + ball.shape.getLocalBounds().height / 2) {
			botPaddle.movingUp = true;
			botPaddle.movingDown = false;
		}
		else {
			botPaddle.movingUp = false;
			botPaddle.movingDown = true;
		}

		if (botPaddle.pos.y <= OFFSET_TOP) {
			paddle.movingUp = false;
		}
		else if (botPaddle.pos.y + paddle.shape.getLocalBounds().height >= HEIGHT) {
			paddle.movingDown = false;
		}


		if (paddle.pos.y <= OFFSET_TOP) {
			paddle.movingUp = false;
		}
		else if (paddle.pos.y + paddle.shape.getLocalBounds().height >= HEIGHT) {
			paddle.movingDown = false;
		}

		// vertical bounds check
		if (ball.pos.y + ball.shape.getLocalBounds().height >= HEIGHT) {
			ball.speedY *= -1;
		}
		else if (ball.pos.y <= 0) {
			ball.speedY *= -1;
		}
		else if (rectsAreColliding(paddle.shape.getGlobalBounds(), ball.shape.getGlobalBounds())) {
			ball.speedX *= -1;
		}
		else if (rectsAreColliding(botPaddle.shape.getGlobalBounds(), ball.shape.getGlobalBounds())) {
			ball.speedX *= -1;
		}


		paddle.update(dt);
		botPaddle.update(dt);
		ball.update(dt);

		// draw
		window.clear();

		//  draw elements
		window.draw(scoreText);
		window.draw(paddle.shape);
		window.draw(botPaddle.shape);
		window.draw(ball.shape);

		window.display();

	}
	return 0;
}

bool rectsAreColliding(const sf::FloatRect& a, const sf::FloatRect& b) {
	if (a.left + a.width < b.left
		|| a.left > b.left + b.width
		|| a.top + a.height < b.top
		|| a.top > b.top + b.height
		) {
		return false;
	}

	return true;
}