#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <fstream>
#include <iostream>

char getKeyCode(int);

struct TextBox {
	sf::RectangleShape txtBox;
	sf::RectangleShape cursor;
	std::string leftText;
	std::string rightText;
	sf::Text text;
};

class Menu {
public:
	virtual void initObjects() = 0;
	virtual void updateButtons(Menu*&, sf::RenderWindow*, int) = 0;
	virtual void enterButtonPressed(Menu*& currentMenu) = 0;
	void initButton(int, int, int, int, sf::Color, int, sf::Color);
	void initLabel(int, int, int, std::string, sf::Color);
	void initTextBox(int, int, int, int, sf::Color, int, sf::Color);
	void drawWindow(sf::RenderWindow*);
	
	std::vector <sf::RectangleShape*> listOfBtns;
	std::vector <sf::Text*> listOfLabels;
	std::vector <TextBox*> listOfTextBoxxes;
	
	sf::Font bankaiFont;
	std::ifstream* readFile;

	static bool userMenuOpen;
	static bool fileUpdate;

	struct File {
		std::fstream* savedFile;
		std::string output;
		std::string fileName;
		int lines = 0;
		
		File(std::string userName){
			std::cout << userName;
			savedFile = new std::fstream;
			fileName = userName + ".txt";
		}
		void getLines(Menu*&);
	};

	File* file;
};



class MainMenu : public Menu {
public:
	void initObjects();
	void updateButtons(Menu*&, sf::RenderWindow*, int);
	void enterButtonPressed(Menu*& currentMenu) {} //for the sake of haveing virutal function, this function does nothing
};

class LoginMenu : public Menu {
public:
	void initObjects();
	void updateButtons(Menu*&, sf::RenderWindow*, int);
	bool login();
	void openSavedFile(Menu*&);
	void enterButtonPressed(Menu*& currentMenu);
};
class UserMenu : public Menu {
public:
	void initObjects();
	void updateButtons(Menu*&, sf::RenderWindow*, int);
	void enterButtonPressed(Menu*& currentMenu);
};

#endif // !1




