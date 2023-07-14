#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <iostream>

class Menu {
public:
	virtual void initObjects() = 0;
	virtual void updateButtons(Menu*&, sf::RenderWindow*, int) = 0;
	void initButton(int, int, int, int, sf::Color, int, sf::Color);
	void initLabel(int, int, int, std::string, sf::Color);
	sf::Font bankaiFont;
	std::vector <sf::RectangleShape*> listOfBtns;
	std::vector <sf::Text*> listOfLabels;

	void drawWindow(sf::RenderWindow*);
};

class MainMenu : public Menu {
public:
	void initObjects();
	void updateButtons(Menu*&, sf::RenderWindow*, int);
};

class LoginMenu : public Menu {
public:
	void initObjects();
	void updateButtons(Menu*&, sf::RenderWindow*, int);
};






