#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <iostream>


#define MAIN_MENU 0
#define LOGIN_MENU 1	
#define NEW_ACCOUNT_MENU 2

class TextBox
{
private:
	sf::Font font;
public:
	TextBox() {
		std::cout << "created";
		cursor = new sf::RectangleShape;
	}

	~TextBox(){
		std::cout << "destroyed";
	}

	sf::RectangleShape* box;
	sf::RectangleShape* cursor;
	sf::Text* input = new sf::Text;
	std::string inputText;

	void initializeCursor(int x, int y, int length, int height, sf::Color fillColor) {
		cursor->setPosition(x, y);
		cursor->setSize(sf::Vector2f(length, height));
		cursor->setFillColor(fillColor);
	}
	
	void typeInput(int x, int y) {
		font.loadFromFile("Res/Fonts/bankai.otf");
		input->setPosition(x, y);
		input->setCharacterSize(40);
		input->setFillColor(sf::Color::White);
		input->setFont(font);
		input->setString(inputText);
	}
};

class Menu
{
public:
	virtual void initObjects() = 0;
	virtual void updateButtons(Menu*&,sf::RenderWindow*, int) = 0;
	void drawObjects(sf::RenderWindow*);
	void initButton(int, int, int, int, sf::Color, int, sf::Color);
	void initLabel(int, int, int, std::string, sf::Color);
	void initTextBox(int,int,int,int,sf::Color);
	sf::Font bankaiFont;
	std::vector <sf::RectangleShape*> listOfBtns;
	std::vector <sf::Text*> listOfLabels;
	std::vector <TextBox*> listOfTextBoxes;
};

class MainMenu : public Menu {
public:
	void initObjects();
	void updateButtons(Menu*&,sf::RenderWindow*, int);
};

class LoginMenu : public Menu {
public:
	void initObjects();
	void updateButtons(Menu*&, sf::RenderWindow*, int);
};

class NewAccountMenu : public Menu {
public:
	void initObjects();
	void updateButtons(Menu*&, sf::RenderWindow*, int);
};
