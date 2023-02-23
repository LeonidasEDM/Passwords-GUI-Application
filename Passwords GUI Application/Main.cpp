#include "Menu.h"

sf::Event evt;
sf::RenderWindow* mainWindow;
void updateWindow(sf::RenderWindow*,Menu*);
void updateButton(int,sf::RenderWindow*,Menu*);
void drawWindow(sf::RenderWindow*, Menu*);

std::vector <sf::RenderWindow*> listOfWindows;

int main() {
	listOfWindows.emplace_back(new sf::RenderWindow(sf::VideoMode(900, 700), "Manage Passwords Program", sf::Style::Titlebar | sf::Style::Close));
	mainWindow = listOfWindows.at(0);
	Menu* menu = new MainMenu;

	drawWindow(mainWindow,menu); //Draw Initial Window

	while (mainWindow->isOpen()) { //Update all windows(if there is more than one window)
		for (sf::RenderWindow* window : listOfWindows) {
			updateWindow(window,menu);
		}
	}
}

void drawWindow(sf::RenderWindow* window, Menu* menu) {
	window->clear(sf::Color(32,17,65,255));
	menu->initObjects(); //Initialize Objects in Menu
	menu->drawObjects(window); //Draw Objects in the Window
	window->display();
}

void updateWindow(sf::RenderWindow* window,Menu* menu) {
	while (window->pollEvent(evt)) { //Event Identifier
		switch (evt.type)
		{
		case sf::Event::Closed: //Close Window Even
			window->close();
			break;

		case sf::Event::MouseButtonPressed:
			for (int i = 0; i < menu->listOfBtns.size(); i++) {
				if (menu->listOfBtns[i]->getGlobalBounds().contains(sf::Mouse::getPosition(*window).x, sf::Mouse::getPosition(*window).y)) {
					updateButton(i,window,menu);
				}
			}
			break;
		}
	}
}

void updateButton(int btnNum, sf::RenderWindow* window,Menu* menu) {
	Menu* temp = menu;
	switch (btnNum)
	{
	case 0:
		menu = new LoginMenu;
		drawWindow(window,menu);
		break;
	case 1: 
		menu = new NewAccountMenu;
		drawWindow(window, menu);
	}
}

