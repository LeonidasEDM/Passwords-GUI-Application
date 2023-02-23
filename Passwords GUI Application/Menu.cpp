#include "Menu.h"

void Menu::drawObjects(sf::RenderWindow* window) {
	for (sf::RectangleShape* btn : this->listOfBtns) { //Draw Buttons
		window->draw(*btn);
	}

	for (sf::Text* txt : this->listOfLabels) { //Draw Labels
		window->draw(*txt);
	}
}
void MainMenu::initObjects() {
	//Initialize Buttons
	for (int i = 0; i < 2; i++) { 
		listOfBtns.emplace_back(new sf::RectangleShape);
		listOfBtns[i]->setSize(sf::Vector2f(225, 75));
		listOfBtns[i]->setPosition(btnPos_X[i], btnPos_Y[i]);
		listOfBtns[i]->setFillColor(sf::Color::Black);
		listOfBtns[i]->setOutlineThickness(2);
		listOfBtns[i]->setOutlineColor(sf::Color::Cyan);
	}
	
	//Initialize TextLabels
	bankaiFont.loadFromFile("Res/Fonts/bankai.otf");
	for (int i = 0; i < 3; i++) {
		listOfLabels.emplace_back(new sf::Text);
		listOfLabels[i]->setString(label_txt[i]);
		listOfLabels[i]->setFillColor(sf::Color::Cyan);
		i == 0 ? listOfLabels[i]->setCharacterSize(50) : listOfLabels[i]->setCharacterSize(27);
		listOfLabels[i]->setPosition(labelPos_X[i], labelPos_Y[i]);
		listOfLabels[i]->setFont(bankaiFont);
	}
}

void LoginMenu::initObjects() {
	//Initialize Buttons
	for (int i = 0; i < 2; i++) {
		listOfBtns.emplace_back(new sf::RectangleShape);
		listOfBtns[i]->setSize(sf::Vector2f(125, 50));
		listOfBtns[i]->setPosition(btnPos_X[i], btnPos_Y[i]);
		listOfBtns[i]->setFillColor(sf::Color::Black);
		listOfBtns[i]->setOutlineThickness(2);
		listOfBtns[i]->setOutlineColor(sf::Color::Cyan);
	}
}

void NewAccountMenu::initObjects() {

}
