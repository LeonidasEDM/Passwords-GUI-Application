#include "Menu.h"

void Menu::drawObjects(sf::RenderWindow* window) {
	for (sf::RectangleShape* btn : this->listOfBtns) { //Draw Buttons
		window->draw(*btn);
	}

	for (sf::Text* txt : this->listOfLabels) { //Draw Labels
		window->draw(*txt);
	}

	for (sf::RectangleShape* txtBox : this->listOfTextBoxes) { //Draw Text Boxes
		window->draw(*txtBox);
	}
}

void Menu::initButton(int length, int height, int x, int y, sf::Color fillColor, int outlineThickness, sf::Color outlineColor) {
	sf::RectangleShape* btn = new sf::RectangleShape;
	btn->setSize(sf::Vector2f(length, height));
	btn->setPosition(x, y);
	btn->setFillColor(fillColor);
	btn->setOutlineThickness(outlineThickness);
	btn->setOutlineColor(outlineColor);
	listOfBtns.emplace_back(btn);
}

void Menu::initLabel(int x, int y, int charSize, std::string text, sf::Color fillColor) {
	sf::Text* txt = new sf::Text;
	txt->setPosition(x, y);
	txt->setCharacterSize(charSize);
	txt->setString(text);
	txt->setFillColor(fillColor);
	txt->setFont(bankaiFont);
	listOfLabels.emplace_back(txt);
}

void Menu::initTextBox(int length, int height, int x, int y, sf::Color fillColor) {
	sf::RectangleShape* txtBox = new sf::RectangleShape;
	txtBox->setSize(sf::Vector2f(length, height));
	txtBox->setPosition(x, y);
	txtBox->setFillColor(fillColor);
	listOfTextBoxes.emplace_back(txtBox);
}

void MainMenu::initObjects() {
	//Initialize Buttons
	initButton(225,75, 345, 355,sf::Color::Black,2,sf::Color::Cyan);
	initButton(225,75, 345, 455,sf::Color::Black,2,sf::Color::Cyan);
	
	
	//Initialize TextLabels
	bankaiFont.loadFromFile("Res/Fonts/bankai.otf");
	initLabel(290,150,50, "Password Manager",sf::Color::Cyan);
	initLabel(427,375,27, "Login",sf::Color::Cyan);
	initLabel(392,477,27, "New Account",sf::Color::Cyan);
}

void LoginMenu::initObjects() {
	//Initialize Buttons
	initButton(125, 50, 150, 555, sf::Color::Black, 2, sf::Color::Cyan);
	initButton(125, 50, 650, 555, sf::Color::Black, 2, sf::Color::Cyan);
	

	//Initialize TextLabels
	bankaiFont.loadFromFile("Res/Fonts/bankai.otf");
	initLabel(182, 562, 27, "Back", sf::Color::Cyan);
	initLabel(682, 562, 27, "Login", sf::Color::Cyan);
	initLabel(265, 225, 30, "Username", sf::Color::Cyan);
	initLabel(265, 330, 30, "Password", sf::Color::Cyan);

	//Initiialize TextBoxes
	initTextBox(410,45,265,270,sf::Color(70,70,70,255));
	initTextBox(410,45,265,370,sf::Color(70,70,70,255));
}

void NewAccountMenu::initObjects() {
	//Initialize Buttons
	initButton(125, 50, 150, 555, sf::Color::Black, 2, sf::Color::Cyan);
	initButton(125, 50, 650, 555, sf::Color::Black, 2, sf::Color::Cyan);

	//Initialize TextLabels
	bankaiFont.loadFromFile("Res/Fonts/bankai.otf");
	initLabel(182, 562, 27, "Back", sf::Color::Cyan);
	initLabel(678, 562, 27, "Create", sf::Color::Cyan);
	initLabel(265, 225, 30, "New Username", sf::Color::Cyan);
	initLabel(265, 330, 30, "New Password", sf::Color::Cyan);

	//Initiialize TextBoxes
	initTextBox(410, 45, 265, 270, sf::Color(70, 70, 70, 255));
	initTextBox(410, 45, 265, 370, sf::Color(70, 70, 70, 255));
}

