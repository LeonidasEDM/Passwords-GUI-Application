
#include "Menu.h"

char keyCodes[100];
Menu* menu;
sf::Event evt;
sf::RenderWindow* mainWindow;
void updateWindow(sf::RenderWindow*);
void drawWindow(sf::RenderWindow*);
void initKeyCodes();
std::vector <sf::RenderWindow*> listOfWindows;
std::vector <sf::Text*> updatedText;

int main() {
	initKeyCodes(); //Initializes valid keyboard inputs for the user
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

template <typename objReturnType> void drawUpdate(sf::RenderWindow* window, objReturnType* object) {
	window->clear(sf::Color(32, 17, 65, 255));
	menu->drawObjects(window);
	window->draw(*object);
	for (sf::Text* txt : updatedText) {
		window->draw(*txt);
	}
	window->display();
}

void drawWindow(sf::RenderWindow* window) {
	window->clear(sf::Color(32,17,65,255));
	menu->initObjects(); //Initialize Objects in Menu
	menu->drawObjects(window); //Draw Objects in the Window
	window->display();
}


char keyCode(int key) {
	if (key > 36) {
		return keyCodes[key-12];
	}
	else {
		return keyCodes[key];
	}
}

void updateWindow(sf::RenderWindow* window) {

	static bool update = false; //Window Debugging bool to prevent interactions between different menus
	static bool textBoxFocus = false;
	static TextBox* activeTxtBox = nullptr; //Pointer to make code more understandable (temporary)

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
				textBoxFocus = false;
			}
			if (update == false) { //Textboxes
				for (int i = 0; i < menu->listOfTextBoxes.size(); i++) {
					if (menu->listOfTextBoxes.at(i)->box->getGlobalBounds().contains(sf::Mouse::getPosition(*window).x, sf::Mouse::getPosition(*window).y)) {
						textBoxFocus = true;
						activeTxtBox = menu->listOfTextBoxes.at(i);
						activeTxtBox->initializeCursor(sf::Mouse::getPosition(*window).x, activeTxtBox->box->getPosition().y + 4, 2.5, 38, sf::Color::White);
						drawUpdate <sf::RectangleShape> (window,activeTxtBox->cursor);

							//Ensures text remains visible in the present menu
							if (updatedText.empty()) {
								updatedText.emplace_back(activeTxtBox->input);
							}
							else {
								for (sf::Text* txt : updatedText) {
									if (txt != activeTxtBox->input) {
										updatedText.emplace_back(activeTxtBox->input);
									}
								}
							}
;					}
				}
			}

			update = false;
			break;

		case sf::Event::KeyPressed: //KEYBOARD INPUT
			
			if (textBoxFocus == true) {
				if (evt.key.shift) {
					std::cout << "YES";
				}
				else {
					std::cout << "error\n" << evt.key.code;
				}

				if (evt.key.code == 59) { //Erase
					if (!activeTxtBox->inputText.empty()) {
						activeTxtBox->inputText.pop_back();
					}
				}
				else if (evt.key.code <= 35 || (evt.key.code >= 48 && evt.key.code <= 52)) { //Valid Inputs from the keyboard ( 0->26 = a->z , 27->35 = 0->9, 48->52 = Special Characters ) 
					activeTxtBox->inputText += (keyCode(evt.key.code));
				}
				else {
					std::cout << "error\n" << evt.key.code;
				}
			}
			activeTxtBox->typeInput(activeTxtBox->box->getPosition().x + 5, activeTxtBox->box->getPosition().y); //TYPE LOCATION
			drawUpdate <sf::Text>(window, activeTxtBox->input);
			break;
		}
	}
}

void MainMenu::updateButtons(Menu*& currentMenu,sf::RenderWindow* window, int btn) {
	updatedText.clear();
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
	//Ensure Deleations of objects(Remainder)
	//Ex: delete menu->listOfTextBoxes.at(0);
	updatedText.clear(); //Clears Updated text if user switches from a different menu
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
	updatedText.clear();
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

void initKeyCodes() {
	enum alphabet { a = 0, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z};
	char specialCharacters[5] { ';', ',', '.', '\'', '/' };
	alphabet letter;
	for (int i = 0; i < 41; i++) {
		letter = static_cast<alphabet>(i);
		if (i < 26) {
			keyCodes[i] = static_cast<char>(letter + 97);
		}
		else if (i == 26) {
			keyCodes[i] = '0';
		}
		else if (i >= 27 &&  i < 36) {
			keyCodes[i] = static_cast<char>(letter + 22);
		}
		else {
			static int sc = 0;
				keyCodes[i] = specialCharacters[sc];
				sc++;
		}
		std::cout << keyCodes[i] << " ";
	}
}