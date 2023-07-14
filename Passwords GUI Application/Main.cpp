#include "Menu.h"

Menu* menu; 
sf::Event evt;

std::vector <sf::RenderWindow*> listOfWindows;

int main() {
	sf::RenderWindow* MainWindow = new sf::RenderWindow(sf::VideoMode(900, 700), "Manage Passwords Program", sf::Style::Titlebar | sf::Style::Close); //Create Main Window
	listOfWindows.emplace_back(MainWindow); //Add Main Window to list

	menu = new MainMenu;
	menu->initObjects();
	menu->drawWindow(MainWindow);

	while (!listOfWindows.empty() && MainWindow->isOpen()) {
		static bool update = false;
		bool windowClosed = false; //Debugging Variable

		for (int i = 0; i < listOfWindows.size(); i++) {
			while (listOfWindows.at(i)->pollEvent(evt)) { //Event Identifier
				switch (evt.type)
				{
				case sf::Event::Closed: //Close Window Even
					windowClosed = true;
					listOfWindows.at(i)->close();
					listOfWindows.erase(listOfWindows.begin() + i);
					break;
				case sf::Event::MouseButtonPressed:
					if (update == false) {
						for (int j = 0; j < menu->listOfBtns.size(); j++) {
							if (menu->listOfBtns.at(j)->getGlobalBounds().contains(sf::Mouse::getPosition(*MainWindow).x, sf::Mouse::getPosition(*MainWindow).y)) {
								update = true;
								menu->updateButtons(menu, MainWindow, j); //Update Buttons
								menu->initObjects();
								menu->drawWindow(MainWindow);
							}
						}
					}

					update = false;
					break;
				}
				if (windowClosed || listOfWindows.empty()) { //Debug list of windows Vector
					break;
				}
			}
			if (windowClosed) { //Debug single Closed window
				windowClosed = false;
				break;
			}
		}
	}
}


