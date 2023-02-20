#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <iostream>
template <typename a> void as();
class Menu
{
private:

public:
	virtual void initObjects() = 0;
	
};

class MainMenu : public Menu {
private:
	sf::RectangleShape** listOfBtns;
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

template <typename a> void as() {
	if (a == Menu) {
		std::cout << "lol";
	}
}