#include <fmt/core.h>
#include <SFML/Graphics.hpp>
#include "Paddle.h"
#include "Ball.h"


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

	bool paused = false;
	int playerScore = 0;
	int botScore = 0;
	sf::Text scoreText;
	scoreText.setFont(font);
	scoreText.setString(fmt::format("Bot: {} | Player: {}", botScore, playerScore));
	scoreText.setFillColor(sf::Color::White);
	scoreText.setPosition(20, 20);
	scoreText.setCharacterSize(28);


	sf::Text pausedText;
	pausedText.setFont(font);
	pausedText.setString("");
	pausedText.setFillColor(sf::Color::White);
	pausedText.setCharacterSize(40);

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
		if (paused) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
				ball.setPosition(WIDTH / 2.0f - ball.shape.getLocalBounds().width / 2, HEIGHT / 2.0f + OFFSET_TOP - ball.shape.getLocalBounds().height / 2.0f);
				paddle.setPosition(WIDTH - paddle.shape.getLocalBounds().width - OFFSET_X, HEIGHT / 2.0f + OFFSET_TOP - paddle.shape.getLocalBounds().height / 2.0f);
				botPaddle.setPosition(OFFSET_X, HEIGHT / 2.0f + OFFSET_TOP - botPaddle.shape.getLocalBounds().height / 2.0f);
				paused = false;
				pausedText.setString("");

			}
		}
		else {

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
			// check game over
			if (ball.pos.x + ball.shape.getLocalBounds().width < botPaddle.pos.x
				|| ball.pos.x > paddle.pos.x + paddle.shape.getLocalBounds().width) {
				if (ball.pos.x < WIDTH / 2.0f) {
					playerScore += 1;
				}
				else {
					botScore += 1;
				}
				scoreText.setString(fmt::format("Bot: {} | Player: {}", botScore, playerScore));

				// pause text
				pausedText.setString("Enter to continue");
				pausedText.setOrigin(pausedText.getLocalBounds().width / 2, pausedText.getLocalBounds().height / 2);
				pausedText.setPosition(WIDTH / 2.0f, HEIGHT / 2.0f + OFFSET_TOP);
				paused = true;
			}
			// limit player's paddle bounds
			if (paddle.pos.y < OFFSET_TOP) {
				paddle.movingUp = false;
			}
			else if (paddle.pos.y + paddle.shape.getLocalBounds().height > HEIGHT) {
				paddle.movingDown = false;
			}

			// move bot paddle
			if (botPaddle.pos.y + botPaddle.shape.getLocalBounds().height / 2.0f > ball.pos.y + ball.shape.getLocalBounds().height / 2
				|| (ball.pos.y > HEIGHT / 2.0f + OFFSET_TOP && ball.speedY < 0)) {
				botPaddle.movingUp = true;
				botPaddle.movingDown = false;
			}
			else {
				botPaddle.movingUp = false;
				botPaddle.movingDown = true;
			}

			if (botPaddle.pos.y < OFFSET_TOP) {
				botPaddle.movingUp = false;
			}
			else if (botPaddle.pos.y + botPaddle.shape.getLocalBounds().height >= HEIGHT) {
				botPaddle.movingDown = false;
			}




			// vertical bounds check
			if (ball.pos.y + ball.shape.getLocalBounds().height >= HEIGHT) {
				ball.speedY *= -1;
			}
			else if (ball.pos.y <= 0) {
				ball.speedY *= -1;
			}
			
			if (ball.pos.x + ball.shape.getLocalBounds().width >= paddle.pos.x
				&& ball.pos.y + ball.shape.getLocalBounds().height > paddle.pos.y
				&& ball.pos.y < paddle.pos.y + paddle.shape.getLocalBounds().height) {
				ball.speedX *= -1;
			}
			else if (ball.pos.x <= botPaddle.pos.x + botPaddle.shape.getLocalBounds().width
				&& ball.pos.y + ball.shape.getLocalBounds().height > botPaddle.pos.y
				&& ball.pos.y < botPaddle.pos.y + botPaddle.shape.getLocalBounds().height) {
				ball.speedX *= -1;
			}


			paddle.update(dt);
			botPaddle.update(dt);
			ball.update(dt);
		} // if !paused

		// draw
		window.clear();

		//  draw elements
		window.draw(scoreText);
		window.draw(paddle.shape);
		window.draw(botPaddle.shape);
		window.draw(ball.shape);
		window.draw(pausedText);

		window.display();

	}
	return 0;
}

