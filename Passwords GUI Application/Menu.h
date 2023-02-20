#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <iostream>

class Menu
{
private:

public:
	virtual void initObjects() = 0;
	void drawObjects(sf::RenderWindow*);
	std::vector <sf::RectangleShape*> listOfBtns;
};

class MainMenu : public Menu {
private:
	int btnPos_X[2] = {345,345};
	int btnPos_Y[2] = {355,455};
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
