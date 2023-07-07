#include "Menu.h"

sf::Event evt;

std::vector <sf::RenderWindow*> listOfWindows;
void initWindows();

int main() {
	sf::RenderWindow* MainWindow = new sf::RenderWindow(sf::VideoMode(900, 700), "Manage Passwords Program", sf::Style::Titlebar | sf::Style::Close); //Create Main Window
	
	listOfWindows.emplace_back(MainWindow); //Add Main Window to list
	initWindows(); //Display Windows

	while (!listOfWindows.empty() && MainWindow->isOpen()) {
		bool windowClosed = false; //Closeing Window Debugger (Many Windows Open)

		for (int i = 0; i < listOfWindows.size(); i++) {
			while (listOfWindows.at(i)->pollEvent(evt)) { //Event Identifier
				switch (evt.type)
				{
				case sf::Event::Closed: //Close Window Even
					windowClosed = true;
					listOfWindows.at(i)->close();
					listOfWindows.erase(listOfWindows.begin() + i);
					break;
				}
				if (windowClosed || listOfWindows.empty()) {
					break;
				}
			}
			if (windowClosed) {
				windowClosed = false;
				break;
			}
		}
	}
}

void initWindows() {
	for (sf::RenderWindow* window : listOfWindows) {
		window->clear(sf::Color(32, 17, 65, 255));
		window->display();
	}
}