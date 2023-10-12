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
	bool password;
};



class Menu {
public:
	virtual void initObjects() = 0;
	virtual void updateButtons(Menu*&, int) = 0;
	virtual void enterButtonPressed(Menu*& currentMenu) = 0;
	void initButton(int, int, int, int, sf::Color, int, sf::Color);
	void initLabel(int, int, int, std::string, sf::Color);
	void initTextBox(int, int, int, int, sf::Color, int, sf::Color, bool);
	void drawWindow(sf::RenderWindow*);
	void saveChanges(Menu*& menu);

	std::vector <sf::RectangleShape*> listOfBtns;
	std::vector <sf::Text*> listOfLabels;
	std::vector <TextBox*> listOfTextBoxxes;
	
	sf::Font bankaiFont;
	std::ifstream* readFile;

	static bool userMenuOpen;
	static bool fileUpdate;

};



class MainMenu : public Menu {
public:
	void initObjects();
	void updateButtons(Menu*&, int);
	void enterButtonPressed(Menu*& currentMenu) {} //for the sake of haveing virutal function, this function does nothing
};

class LoginMenu : public Menu {
public:
	void initObjects();
	void updateButtons(Menu*&, int);
	bool login();
	void enterButtonPressed(Menu*& currentMenu);
};
class UserMenu : public Menu {
public:
	void initObjects();
	void updateButtons(Menu*&, int);
	void enterButtonPressed(Menu*& currentMenu);

};
class Error : public  Menu {
public:
	void initObjects();
	void updateButtons(Menu*&, int);
	void enterButtonPressed(Menu*& currentMenu);

};



struct File {
	std::fstream* savedFile;
	std::ifstream* readFile;
	std::ofstream* writeFile;
	std::string fileName;
	std::string* Pw = new std::string;
	int lines = 0;

	File(std::string userName) {
		std::cout << userName;
		savedFile = new std::fstream;
		fileName = userName + ".txt";
	}
	void getLines(Menu*&);
	void openSavedFile(Menu*&);
};

#endif // !1




