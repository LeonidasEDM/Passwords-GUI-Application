#pragma once
#include "Menu.h"

class TextBox
{
public:
	sf::RectangleShape* cursor = new sf::RectangleShape;
	sf::Text* input = new sf::Text;
	std::string inputText;
	void initializeCursor(int x,int y,int length, int height, sf::Color fillColor, sf::RenderWindow*& window,Menu* menu) {
		cursor->setPosition(x,y);
		cursor->setSize(sf::Vector2f(length, height));
		cursor->setFillColor(fillColor);
		window->clear(sf::Color(32, 17, 65, 255));
		menu->drawObjects(window);
		window->draw(*cursor);
		window->display();
	}
	void typeInput(int x, int y, sf::RenderWindow*& window, Menu* menu) {
		window->clear(sf::Color(32, 17, 65, 255));
		menu->drawObjects(window);
		input->setPosition(x,y);
		input->setCharacterSize(50);
		input->setFillColor(sf::Color::White);
		input->setFont(menu->bankaiFont);
		input->setString(inputText);
		window->draw(*input);
		window->display();
	}
};

