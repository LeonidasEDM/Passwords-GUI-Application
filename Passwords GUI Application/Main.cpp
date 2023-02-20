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
		}
	}
}

