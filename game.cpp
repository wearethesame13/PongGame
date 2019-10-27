#include "game.h"
#include <SFML/Graphics.hpp>
#include "ball.h"
#include "paddle.h"
using namespace sf;
Game::Game()
	:mWindow(sf::VideoMode(gameWidth,gameHeight , 32), "PongGame", sf::Style::Titlebar | sf::Style::Close)
{
	isPlaying = false;
	AITime = sf::seconds(0.1f);
	paddleSpeed = 400.f;
	rightPaddleSpeed = 0.f;
	ballSpeed = 400.f;
	ballAngle = 0.f;
	pi = 3.14159f;
	text.message.setString("Welcome to pong game\nPress space to play");
}
void Game::run()
{
	mWindow.setVerticalSyncEnabled(true);
	isPlaying = false;
	std::srand(static_cast<unsigned int>(std::time(NULL)));
	while (mWindow.isOpen())
	{
		processEvents();
		update();
		render();
	}
}
void Game::update()
{
	if (isPlaying)
	{
		float deltaTime = clock.restart().asSeconds();

		// Move the player's paddle
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) &&
			(left.Paddle.getPosition().y - paddleSize.y / 2 > 5.f))
		{
			left.Paddle.move(0.f, -paddleSpeed * deltaTime);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) &&
			(left.Paddle.getPosition().y + paddleSize.y / 2 < gameHeight - 5.f))
		{
			left.Paddle.move(0.f, paddleSpeed * deltaTime);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) &&
			(right.Paddle.getPosition().y - paddleSize.y / 2 > 5.f))
		{
			right.Paddle.move(0.f, -paddleSpeed * deltaTime);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) &&
			(right.Paddle.getPosition().y + paddleSize.y / 2 < gameHeight - 5.f))
		{
			right.Paddle.move(0.f, paddleSpeed * deltaTime);
		}

		// Move the ball
		float factor = ballSpeed * deltaTime;
		this->pong.ball.move(std::cos(ballAngle) * factor, std::sin(ballAngle) * factor);

		// Check collisions between the ball and the screen
		if (this->pong.ball.getPosition().x - this->pong.ballRadius < 0.f)
		{
			isPlaying = false;
			text.message.setString("You lost!\nPress space to restart or\nescape to exit");
		}
		if (this->pong.ball.getPosition().x + this->pong.ballRadius > gameWidth)
		{
			isPlaying = false;
			text.message.setString("You won!\nPress space to restart or\nescape to exit");
		}
		if (this->pong.ball.getPosition().y - this->pong.ballRadius < 0.f)
		{

			ballAngle = -ballAngle;
			this->pong.ball.setPosition(this->pong.ball.getPosition().x, this->pong.ballRadius + 0.1f);
		}
		if (this->pong.ball.getPosition().y + this->pong.ballRadius > gameHeight)
		{
			ballAngle = -ballAngle;
			this->pong.ball.setPosition(this->pong.ball.getPosition().x, gameHeight - this->pong.ballRadius - 0.1f);
		}

		// Check the collisions between the ball and the paddles
		// Left Paddle
		if (this->pong.ball.getPosition().x - this->pong.ballRadius < left.Paddle.getPosition().x + paddleSize.x / 2 &&
			this->pong.ball.getPosition().x - this->pong.ballRadius > left.Paddle.getPosition().x&&
			this->pong.ball.getPosition().y + this->pong.ballRadius >= left.Paddle.getPosition().y - paddleSize.y / 2 &&
			this->pong.ball.getPosition().y - this->pong.ballRadius <= left.Paddle.getPosition().y + paddleSize.y / 2)
		{
			if (this->pong.ball.getPosition().y > this->left.Paddle.getPosition().y)
				ballAngle = pi - ballAngle + (std::rand() % 20) * pi / 180;
			else
				ballAngle = pi - ballAngle - (std::rand() % 20) * pi / 180;

			this->pong.ball.setPosition(this->left.Paddle.getPosition().x + this->pong.ballRadius + paddleSize.x / 2 + 0.1f, this->pong.ball.getPosition().y);
		}

		// Right Paddle
		if (this->pong.ball.getPosition().x + this->pong.ballRadius > this->right.Paddle.getPosition().x - paddleSize.x / 2 &&
			this->pong.ball.getPosition().x + this->pong.ballRadius < this->right.Paddle.getPosition().x &&
			this->pong.ball.getPosition().y + this->pong.ballRadius >= this->right.Paddle.getPosition().y - paddleSize.y / 2 &&
			this->pong.ball.getPosition().y - this->pong.ballRadius <= this->right.Paddle.getPosition().y + paddleSize.y / 2)
		{
			if (this->pong.ball.getPosition().y > this->right.Paddle.getPosition().y)
				ballAngle = pi - ballAngle + (std::rand() % 20) * pi / 180;
			else
				ballAngle = pi - ballAngle - (std::rand() % 20) * pi / 180;

			this->pong.ball.setPosition(this->right.Paddle.getPosition().x - this->pong.ballRadius - paddleSize.x / 2 - 0.1f, this->pong.ball.getPosition().y);
		}
	}
	
}
void Game::render()
{
	mWindow.clear(sf::Color(50, 200, 50));
		// Draw the paddles and the ball
	if (isPlaying)
	{
		mWindow.draw(left.Paddle);
		mWindow.draw(right.Paddle);
		mWindow.draw(pong.ball);
	}
			
	else
	{
		// Draw the pause message
		mWindow.draw(text.message);
	}
	// Display things on screen
	mWindow.display();
}
void Game::processEvents()
{
	sf::Event event;
	while (mWindow.pollEvent(event))
	{
		if ((event.type == sf::Event::Closed) ||
			((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape)))
		{
			mWindow.close();
			break;
		}
		if ((event.type == sf::Event::Closed) ||
			((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Space)))
		{
			if (!isPlaying)
			{
				// (re)start the game
				isPlaying = true;
				clock.restart();

				// Reset the position of the paddles and ball
				left.Paddle.setPosition(10 + paddleSize.x / 2, (float)gameHeight / 2);
				right.Paddle.setPosition(gameWidth - 10 - paddleSize.x / 2,(float) gameHeight / 2);
				pong.ball.setPosition((float) gameWidth / 2, (float) gameHeight / 2);

				// Reset the ball angle
				do
				{
					// Make sure the ball initial angle is not too much vertical
					ballAngle = (std::rand() % 360) * 2 * pi / 360;
				} while (std::abs(std::cos(ballAngle)) < 0.7f);
			}
		}
	}
}

