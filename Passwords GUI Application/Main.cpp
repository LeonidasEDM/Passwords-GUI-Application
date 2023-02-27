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
	while (window->pollEvent(evt)) { //Event Identifier
		switch (evt.type)
		{
		case sf::Event::Closed: //Close Window Even
			window->close();
			break;

		case sf::Event::MouseButtonPressed:
			for (int i = 0; i < menu->listOfBtns.size();i++) {
				if (menu->listOfBtns.at(i)->getGlobalBounds().contains(sf::Mouse::getPosition(*window).x, sf::Mouse::getPosition(*window).y)) {
					menu->updateButtons(menu,window,i); //Update Buttons
					drawWindow(window); //TEMPORARY DRAW
				}
			}
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