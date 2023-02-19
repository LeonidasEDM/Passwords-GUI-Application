#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

sf::Event evt;

void updateWindow(sf::RenderWindow*);
std::vector <sf::RenderWindow*> listOfWindows;

int main() {
	listOfWindows.emplace_back(new sf::RenderWindow(sf::VideoMode(900, 700), "Manage Passwords Program", sf::Style::Titlebar | sf::Style::Close));


	while (listOfWindows.at(0)->isOpen()) {
		for (sf::RenderWindow* window : listOfWindows) {
			updateWindow(window);
		}
	}
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