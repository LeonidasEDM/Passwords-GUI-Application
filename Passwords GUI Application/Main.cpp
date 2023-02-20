#include "Menu.h"

sf::Event evt;
sf::RenderWindow* mainWindow;
void updateWindow(sf::RenderWindow*);
void drawWindow(sf::RenderWindow*);
void drawWindow(sf::RenderWindow*, Menu*);

std::vector <sf::RenderWindow*> listOfWindows;

int main() {
	listOfWindows.emplace_back(new sf::RenderWindow(sf::VideoMode(900, 700), "Manage Passwords Program", sf::Style::Titlebar | sf::Style::Close));
	mainWindow = listOfWindows.at(0);
	Menu* menu = new MainMenu;
	
	drawWindow(mainWindow,menu);

	while (mainWindow->isOpen()) {
		for (sf::RenderWindow* window : listOfWindows) {
			updateWindow(window);
		}
	}
}

void drawWindow(sf::RenderWindow* window, Menu* menu) {
	window->clear(sf::Color(32,17,65,255));
	menu->initObjects();
	
		//window->draw(menu->drawObject());
	
	window->display();
}

void updateWindow(sf::RenderWindow* window) {
	while (window->pollEvent(evt)) {
		switch (evt.type)
		{
		case sf::Event::Closed:
			window->close();
			break;
		}
	}
}

