#include "pauseMessage.h"

pauseMessage::pauseMessage()
{
	sf::Text pauseMessage;
	pauseMessage.setCharacterSize(40);
	pauseMessage.setPosition(170.f, 150.f);
	pauseMessage.setFillColor(sf::Color::White);
	pauseMessage.setString("Welcome to Pong!\nPress space to start the game");
}
