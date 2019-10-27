#include "pauseMessage.h"

pauseMessage::pauseMessage()
{
	sf::Font font;
	font.loadFromFile("resources/sansation.ttf");
	this->message.setFont(font);
	this->message.setCharacterSize(40);
	this->message.setPosition(170.f, 150.f);
	this->message.setFillColor(sf::Color::White);
}
