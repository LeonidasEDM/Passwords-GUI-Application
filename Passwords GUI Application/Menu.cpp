#include "Menu.h"

void MainMenu::initObjects() {
	//Initialize Buttons
	initButton(225, 75, 345, 355, sf::Color::Black, 2, sf::Color::Cyan);
	initButton(225, 75, 345, 455, sf::Color::Black, 2, sf::Color::Cyan);

	//Initialize TextLabels
	bankaiFont.loadFromFile("Res/Fonts/bankai.otf");
	initLabel(290, 150, 50, "Password Manager", sf::Color::Cyan);
	initLabel(427, 375, 27, "Login", sf::Color::Cyan);
	initLabel(392, 477, 27, "New Account", sf::Color::Cyan);
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

	//Initialize TextBoxxes
	initTextBox(350, 35, 267, 272, sf::Color(62, 70, 84, 255), 2, sf::Color(62, 70, 84, 255));
	initTextBox(350, 35, 267, 376, sf::Color(62, 70, 84, 255), 2, sf::Color(62, 70, 84, 255));
}

void Menu::drawWindow(sf::RenderWindow* window)
{
	window->clear(sf::Color(32, 17, 65, 255));

	for (sf::RectangleShape* btn : this->listOfBtns) { //Draw Buttons
		window->draw(*btn);
	}

	for (sf::Text* txt : this->listOfLabels) { //Draw Labels
		window->draw(*txt);
	}

	for (int i = 0; i < listOfTextBoxxes.size(); i++) {
		window->draw(listOfTextBoxxes.at(i)->txtBox);
		window->draw(listOfTextBoxxes.at(i)->text);
	}

	window->display();

}

void MainMenu::updateButtons(Menu*& currentMenu, sf::RenderWindow* window, int btn) {
	listOfBtns.clear();
	listOfLabels.clear();
	delete currentMenu;
	std::cout << btn;
	switch (btn) {
	case 0:
		currentMenu = new LoginMenu;
		break;
	case 1:
		currentMenu = new LoginMenu;
		break;
	}
}

void LoginMenu::updateButtons(Menu*& currentMenu, sf::RenderWindow* window, int btn) {
	listOfBtns.clear();
	listOfLabels.clear();
	delete currentMenu;
	
	switch (btn) {
	case 0:
		currentMenu = new MainMenu;
		break;
	case 1:
		currentMenu = new MainMenu;
		break;
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

void Menu::initTextBox(int length, int height, int x, int y, sf::Color fillColor, int outlineThickness, sf::Color outlineColor) {
	
	TextBox* Box = new TextBox;
	Box->txtBox.setSize(sf::Vector2f(length, height));
	Box->txtBox.setPosition(x, y);
	Box->txtBox.setFillColor(fillColor);
	Box->txtBox.setOutlineThickness(outlineThickness);
	Box->txtBox.setOutlineColor(outlineColor);
	listOfTextBoxxes.emplace_back(Box);

	Box->text.setPosition(x+5, y-5);
	Box->text.setFont(bankaiFont);
	Box->text.setCharacterSize(35);
	Box->text.setFillColor(sf::Color::White);
}

