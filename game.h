#pragma once
#include <SFML\Graphics.hpp>
#include "ball.h"
#include "pauseMessage.h"
#include "paddle.h"
#include <ctime>
#include <cstdlib>
#include <cmath>
class Game
{
public:
	Ball pong;
	paddle left;
	paddle right;
	pauseMessage text;
	sf::Clock AITimer;
	sf::Clock clock;
	sf::Time AITime = sf::seconds(0.1f);
	float paddleSpeed;
	float rightPaddleSpeed;
	float ballSpeed;
	float ballAngle; // to be changed later
	float pi;
	int gameWidth = 800;
	int gameHeight = 600;
	bool isPlaying;
	Game();
	void run();
private:
	void processEvents();
	void update();
	void render();
private:
	sf::RenderWindow mWindow;
};
