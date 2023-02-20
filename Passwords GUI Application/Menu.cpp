#include "Menu.h"

void Menu::drawObjects(sf::RenderWindow* window) {
	for (sf::RectangleShape* btn : this->listOfBtns) { //Draw Buttons
		window->draw(*btn);
	}
}
void MainMenu::initObjects() {
	for (int i = 0; i < 2; i++) { //Initialize Buttons
		listOfBtns.emplace_back(new sf::RectangleShape);
		listOfBtns[i]->setSize(sf::Vector2f(225, 75));
		listOfBtns[i]->setPosition(btnPos_X[i], btnPos_Y[i]);
		listOfBtns[i]->setFillColor(sf::Color::Black);
		listOfBtns[i]->setOutlineThickness(1);
		listOfBtns[i]->setOutlineColor(sf::Color::Cyan);
	}
}

void LoginMenu::initObjects() {

}

void NewAccountMenu::initObjects() {

}
