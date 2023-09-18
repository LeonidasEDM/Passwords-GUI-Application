#include "Menu.h"

char getKeyCode(int);
std::string smallChar(int);
sf::Event evt;

bool Menu::userMenuOpen = false;
bool Menu::fileUpdate = false;

void initErrorInterface();

struct Interface { //Each Graphic Interface that holds a window and a menu
	sf::RenderWindow* window;
	Menu* menu;
};
std::vector <Interface*> listOfInterfaces; //overall list of interfaces use for iteration

int main() {

	TextBox* activeTextBox = nullptr; //activates textbox interaction
	static bool update = false; //MAIN DEBUGGER (Bool debugs interactions between menus and insures a single update at a time)
	bool windowClosed = false; //Debugging Variable

	Interface* mainInterface;
	mainInterface = new Interface;
	listOfInterfaces.emplace_back(mainInterface); //Add Main Window to list
	mainInterface->window = new sf::RenderWindow(sf::VideoMode(900, 700), "Manage Passwords Program", sf::Style::Titlebar | sf::Style::Close); //Create Main Window
	

	mainInterface->menu = new MainMenu;
	mainInterface->menu->initObjects();
	mainInterface->menu->drawWindow(mainInterface->window);

	while (!listOfInterfaces.empty() && mainInterface->window->isOpen()) {
		for (int i = 0; i < listOfInterfaces.size(); i++) {
			Interface* activeInterface = listOfInterfaces.at(i);
			sf::RenderWindow* activeWindow = activeInterface->window;
			Menu*& activeMenu = activeInterface->menu;
			while (activeInterface->window->pollEvent(evt)) { //Event Identifier
				switch (evt.type)
				{
				case sf::Event::Closed: //Close Window Even
					windowClosed = true;
					activeInterface->window->close();
					listOfInterfaces.erase(listOfInterfaces.begin() + i);
					break;

				case sf::Event::MouseButtonPressed:
					if (activeWindow == listOfInterfaces.at(0)->window) {
						activeTextBox = nullptr;
						if (update == false) { //button update T/F
							for (int j = 0; j < activeMenu->listOfBtns.size(); j++) {
								if (activeMenu->listOfBtns.at(j)->getGlobalBounds().contains(sf::Mouse::getPosition(*activeWindow).x, sf::Mouse::getPosition(*activeWindow).y)) {
									update = true;

									if (!activeMenu->fileUpdate)
										activeMenu->updateButtons(activeMenu, j); //Button Update Call
									else {
										if (listOfInterfaces.size() < 2) {
											initErrorInterface(); //Logic only applicable if usermenu is manipulated
										}
									}
								}
							}
						}


						for (int j = 0; j < activeMenu->listOfTextBoxxes.size(); j++) {
							activeMenu->listOfTextBoxxes.at(j)->cursor.setFillColor(sf::Color(255, 255, 255, 0));
							if (update == false) { //TextBox update T/F
								if (activeMenu->listOfTextBoxxes.at(j)->txtBox.getGlobalBounds().contains(sf::Mouse::getPosition(*activeWindow).x, sf::Mouse::getPosition(*activeWindow).y)) {
									activeTextBox = activeMenu->listOfTextBoxxes.at(j);
									activeMenu->listOfTextBoxxes.at(j)->cursor.setFillColor(sf::Color(255, 255, 255, 255));
									;								update = true;
								}
								else {
									activeMenu->listOfTextBoxxes.at(j)->cursor.setFillColor(sf::Color(255, 255, 255, 0));
								}
							}
						}

						activeMenu->drawWindow(activeWindow);

						update = false;
					}
					else {
						listOfInterfaces.at(0)->window->requestFocus(); //If Error Windows is open, It will have main focus
					}
					break;

				case sf::Event::KeyPressed:

					std::string* tempString = nullptr;
					if (activeTextBox != nullptr) {
						activeMenu->userMenuOpen ? std::cout << "OPEN" : std::cout << "Closed";
						if (activeMenu->userMenuOpen) {
							activeMenu->fileUpdate = true;
						}

						if (evt.key.code != -1 && !(36 <= evt.key.code && evt.key.code <= 45 || 58 <= evt.key.code && evt.key.code <= 66 || 71 <= evt.key.code && evt.key.code <= 74) && evt.key.code < 84) { //Debugs certain keys not in use

							//Determines how far text can go in the text box
							if (activeTextBox->text.findCharacterPos(activeTextBox->text.getString().getSize()).x < (activeTextBox->txtBox.getSize().x + activeTextBox->txtBox.getPosition().x - 10)) {
								activeTextBox->leftText = activeTextBox->leftText + getKeyCode(evt.key.code);
							}
						}
						else {
							switch (evt.key.code)
							{
							case 59:
								if (!activeTextBox->leftText.empty()) { //Backspace Limit
									activeTextBox->leftText.pop_back();
								}
								if (evt.key.control) {
									while(!activeTextBox->leftText.empty()) {
										if (activeTextBox->leftText.at(activeTextBox->leftText.size() - 1) == ' ') {
											break;
										}
											activeTextBox->leftText.pop_back();
									}
								}
								break;
							case 60: //Tab Key
								if (activeTextBox != nullptr) {
									activeTextBox->cursor.setFillColor(sf::Color(255, 255, 255, 0));
								}
								for (int i = 0; i < activeMenu->listOfTextBoxxes.size(); i++) {
									if (activeMenu->listOfTextBoxxes.at(i) == activeTextBox) {
										if (i != activeMenu->listOfTextBoxxes.size()- 1) {
											activeTextBox = activeMenu->listOfTextBoxxes.at(i + 1);
											activeTextBox->cursor.setFillColor(sf::Color(255, 255, 255, 255));
											break;
										}
										else {
											activeTextBox = nullptr;
										}
									}
								}
								break;
							case 71: //Left arrow key
								if (!activeTextBox->leftText.empty()) { //Left Limit
									activeTextBox->rightText = activeTextBox->leftText.at(activeTextBox->leftText.size() - 1) + activeTextBox->rightText;
									activeTextBox->leftText.pop_back();
								}
								break;
							case 72: //Right arrow key
								if (!activeTextBox->rightText.empty()) { //Right Limit
									activeTextBox->leftText = activeTextBox->leftText + activeTextBox->rightText.at(0);
									if (activeTextBox->rightText.size() == 1) {
										activeTextBox->rightText.clear();
									}
									else {
										activeTextBox->rightText = activeTextBox->rightText.substr(1, activeTextBox->rightText.size() - 1);
									}
								}
							}

						}

						if (activeTextBox != nullptr) {
							activeTextBox->text.setString(activeTextBox->leftText + activeTextBox->rightText);

							/*
							int char_X = activeTextBox->text.findCharacterPos(activeTextBox->text.getString().getSize() - 1).x;
							int char_Y = activeTextBox->txtBox.getPosition().y;
							int characterSize = activeTextBox->text.getCharacterSize();
							*/

							//Left and right arrow key Logic
							if (activeTextBox->leftText.empty()) { //if textbox is empty
								activeTextBox->cursor.setPosition(activeTextBox->txtBox.getPosition());
							}
							else {
								if (!activeTextBox->rightText.empty()) { //determined if the cursor is positioned between a letter or not
									activeTextBox->cursor.setPosition(sf::Vector2f(activeTextBox->text.findCharacterPos(activeTextBox->leftText.size()).x, activeTextBox->txtBox.getPosition().y));
								}
								else {
									for (int i = 0; i < 30; i++) {
										if (!activeTextBox->text.getString().substring(activeTextBox->leftText.size() - 1, activeTextBox->leftText.size()).find((smallChar(i)))) { //determined if letter is smaller than normal

											activeTextBox->cursor.setPosition(sf::Vector2f(activeTextBox->text.findCharacterPos(activeTextBox->text.getString().getSize() - 1).x + activeTextBox->text.getCharacterSize() * 0.2, activeTextBox->txtBox.getPosition().y));

											break;
										}
										else if (i == 29) { //if letter is a bigger size, cursor is placed a little further back (i == 29 insures that the statment is only run once the loop iterates over the entire list of smallCharacters)
											activeTextBox->cursor.setPosition(sf::Vector2f(activeTextBox->text.findCharacterPos(activeTextBox->text.getString().getSize() - 1).x + activeTextBox->text.getCharacterSize() * 0.5, activeTextBox->txtBox.getPosition().y));
										}
									}
								}
							}

							if (evt.key.code == 58) { //Enter Key (Placed here by itself due to it's logic requiering the conclusion of input)
								activeTextBox->cursor.setFillColor(sf::Color(255, 255, 255, 0));
								activeTextBox = nullptr;
								activeMenu->enterButtonPressed(activeMenu);
							}
						}
						activeMenu->drawWindow(activeWindow);
					}
					break;
				}

				if (windowClosed || listOfInterfaces.empty()) { //Debug list of windows Vector
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

char keyCode_Letters[26] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm','n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z' };
char keyCode_SLetters[26] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M','N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z' };
char keyCode_Numbers[10] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };
char keyCode_SNumbers[10] = { ')', '!', '@', '#', '$', '%', '^', '&', '*', '(' };
char keyCode_Symbols[11] = { '[',']',';',',','.','\'','/','(\)','`','=','-'};
char keyCode_SSymbols[11] = { '{','}',':','<','>','"','?','|','~','+','_'};
char keyCode_Math[4] = { '+','-','*','/' };

char getKeyCode(int key) {
	char output;
	bool display_Text = true;
	//Letters
	if (evt.key.code <= 25) { 
		if (evt.key.shift) {
			output = keyCode_SLetters[key];
		}
		else {
			output = keyCode_Letters[key];
		}
	}

	//Numbers
	else if (evt.key.code <= 35) { 
		
		if (evt.key.shift) {
			output = keyCode_SNumbers[key - 26];
		}
		else {
			output = keyCode_Numbers[key - 26];
		}
	}

	//Symbols
	else if (46 <= evt.key.code && evt.key.code <= 56) { 
		if (evt.key.shift) {
			output = keyCode_SSymbols[key - 46];
		}
		else {
			output = keyCode_Symbols[key - 46];
		}
	}

	//NumPad Numbers
	else if (75 <= evt.key.code && evt.key.code <= 84) {
		output = keyCode_Numbers[key - 75];
	}

	//NumPad Symbols 
	else if (67 <= evt.key.code && evt.key.code <= 70) { 
		output = keyCode_Math[key - 67];
	}

	//Space
	else if (key == 57) {
		output = ' ';
	}

	else {
		display_Text = false;
		
	}
	
	if (display_Text) {
		return output;
	}
}

std::string smallChar(int i) {
	std::string smallCharList[30] = { "f", "i", "j", "l", "t", "I", ")", "!", " ^ ", " * ", "(", "[", "]", ";", ",", ".", "\'", "/", "(\)", "`", "{", "}", ":", "\"", "?", "|", "~", "+", "_", " "};
	return smallCharList[i];
}

void initErrorInterface() {
		Interface* errorInterface;
		errorInterface = new Interface;
		listOfInterfaces.emplace(listOfInterfaces.begin(), errorInterface);
		errorInterface->window = new sf::RenderWindow(sf::VideoMode(480, 220), "Error", sf::Style::Titlebar | sf::Style::Close);
		errorInterface->menu = new Error;
		errorInterface->menu->initObjects();
		errorInterface->menu->drawWindow(errorInterface->window);
}