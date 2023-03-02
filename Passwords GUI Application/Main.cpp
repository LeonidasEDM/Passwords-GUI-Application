#include "Menu.h"

Menu* menu;
sf::Event evt;
sf::RenderWindow* mainWindow;
void updateWindow(sf::RenderWindow*);
void drawWindow(sf::RenderWindow*);
std::vector <sf::RenderWindow*> listOfWindows;

int main() {
	listOfWindows.emplace_back(new sf::RenderWindow(sf::VideoMode(900, 700), "Manage Passwords Program", sf::Style::Titlebar | sf::Style::Close));
	menu = new MainMenu;
	mainWindow = listOfWindows.at(0);
	drawWindow(mainWindow); //Draw Initial Window

	while (mainWindow->isOpen()) { //Update all windows(if there is more than one window)
		for (sf::RenderWindow* window : listOfWindows) {
			updateWindow(window);
		}
	}
}

void drawWindow(sf::RenderWindow* window) {
	window->clear(sf::Color(32,17,65,255));
	menu->initObjects(); //Initialize Objects in Menu
	menu->drawObjects(window); //Draw Objects in the Window
	window->display();
}

void updateWindow(sf::RenderWindow* window) {
	bool update = false;
	bool textBoxFocus = false;
	while (window->pollEvent(evt)) { //Event Identifier
		switch (evt.type)
		{
		case sf::Event::Closed: //Close Window Even
			window->close();
			break;

		case sf::Event::MouseButtonPressed:
			if (update == false) {
				for (int i = 0; i < menu->listOfBtns.size(); i++) {
					if (menu->listOfBtns.at(i)->getGlobalBounds().contains(sf::Mouse::getPosition(*window).x, sf::Mouse::getPosition(*window).y)) {
						update = true;
						menu->updateButtons(menu, window, i); //Update Buttons
						drawWindow(window); //TEMPORARY DRAW
					}
				}
			}
			if (update == false) {
				for (int i = 0; i < menu->listOfTextBoxes.size(); i++) {
					if (menu->listOfTextBoxes.at(i)->getGlobalBounds().contains(sf::Mouse::getPosition(*window).x, sf::Mouse::getPosition(*window).y)) {
						update = true;
						sf::RectangleShape* cursor = new sf::RectangleShape;
						sf::Text* input = new sf::Text;
						cursor->setPosition(sf::Mouse::getPosition(*window).x, menu->listOfTextBoxes.at(i)->getPosition().y + 4);
						input->setPosition(cursor->getPosition().x, cursor->getPosition().y);
						input->setCharacterSize(5);
						cursor->setSize(sf::Vector2f(2.5, 38));
						cursor->setFillColor(sf::Color::White);
						window->clear(sf::Color(32, 17, 65, 255));
						menu->drawObjects(window);
						window->draw(*cursor);
						window->display();
						std::string lol;
						textBoxFocus = true;
					
					}
				}
			}
			update = false;
			break;
		}
	}
}

void MainMenu::updateButtons(Menu*& currentMenu,sf::RenderWindow* window, int btn) {
	delete currentMenu;
	switch (btn) {
	case 0:
		currentMenu = new LoginMenu;
		break;
	case 1:
		currentMenu = new NewAccountMenu;
		break;
	}
}

void LoginMenu::updateButtons(Menu*& currentMenu, sf::RenderWindow* window, int btn) {
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

void NewAccountMenu::updateButtons(Menu*& currentMenu, sf::RenderWindow* window, int btn) {
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

/*
#include <iostream>
#include "Menu.h"
#include <vector>

int main()
{
	sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(900, 700), "Manage Passwords Program", sf::Style::Titlebar | sf::Style::Close);
	sf::Event evt;

	std::vector<sf::RectangleShape*> shapes; // vector to hold all created rectangle shapes

	while (window->isOpen())
	{
		while (window->pollEvent(evt))
		{
			switch (evt.type)
			{
			case sf::Event::Closed:
				window->close();
				break;
			case sf::Event::MouseButtonPressed:
				sf::RectangleShape* n = new sf::RectangleShape;
				n->setPosition(sf::Mouse::getPosition(*window).x, sf::Mouse::getPosition(*window).y);
				n->setSize(sf::Vector2f(10, 10));
				shapes.push_back(n); // add new shape to vector
				break;
			}
		}

		window->clear();

		// draw all created shapes
		for (auto& shape : shapes) {
			window->draw(*shape);
		}

		window->display();
	}

	return 0;
}

*/