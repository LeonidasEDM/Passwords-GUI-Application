#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <iostream>

class Menu
{
public:
	virtual void initObjects() = 0;
	void drawObjects(sf::RenderWindow*);
	sf::Font bankaiFont;
	std::vector <sf::RectangleShape*> listOfBtns;
	std::vector <sf::Text*> listOfLabels;
};

class MainMenu : public Menu {
private:
	int btnPos_X[2] = {345,345};
	int btnPos_Y[2] = {355,455};
	int labelPos_X[3] = {290,427,392};
	int labelPos_Y[3] = {150,375,477};
	std::string label_txt[3] = {"Password Manager","Login","New Account"};
public:
	void initObjects();
};

class LoginMenu : public Menu {
public:
	void initObjects();
};

class NewAccountMenu : public Menu {
public:
	void initObjects();
};
