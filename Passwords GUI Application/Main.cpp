#include "Menu.h"

char getKeyCode(int);

Menu* menu; 
sf::Event evt;

std::vector <sf::RenderWindow*> listOfWindows;


int main() {

	TextBox* activeTextBox = nullptr; //activates textbox interaction
	static bool update = false; //MAIN DEBUGGER (Bool debugs interactions between menus and insures a single update at a time)
	bool windowClosed = false; //Debugging Variable

	sf::RenderWindow* MainWindow = new sf::RenderWindow(sf::VideoMode(900, 700), "Manage Passwords Program", sf::Style::Titlebar | sf::Style::Close); //Create Main Window
	listOfWindows.emplace_back(MainWindow); //Add Main Window to list

	menu = new MainMenu;
	menu->initObjects();
	menu->drawWindow(MainWindow);

	while (!listOfWindows.empty() && MainWindow->isOpen()) {
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
					activeTextBox = nullptr;
						if (update == false) { //button update T/F
							for (int j = 0; j < menu->listOfBtns.size(); j++) {
								if (menu->listOfBtns.at(j)->getGlobalBounds().contains(sf::Mouse::getPosition(*MainWindow).x, sf::Mouse::getPosition(*MainWindow).y)) {
									update = true;
									menu->updateButtons(menu, MainWindow, j); //Update Buttons
									menu->initObjects();
									menu->drawWindow(MainWindow);
								}
							}
						}

					if (update == false) { //TextBox update T/F
						for (int j = 0; j < menu->listOfTextBoxxes.size(); j++) {
							if (menu->listOfTextBoxxes.at(j)->txtBox.getGlobalBounds().contains(sf::Mouse::getPosition(*MainWindow).x, sf::Mouse::getPosition(*MainWindow).y)) {
								activeTextBox = menu->listOfTextBoxxes.at(j);
								
;								update = true;
							}
						}
					}
					update = false;
					break;

				case sf::Event::KeyPressed:
					
					std::string* tempString = nullptr;
					if (activeTextBox != nullptr) {
						if (evt.key.code != -1 && !(36 <= evt.key.code && evt.key.code <= 45 || 58 <= evt.key.code && evt.key.code <= 66 || 71 <= evt.key.code && evt.key.code <= 74) && evt.key.code < 84) { //Debugs certain keys not in use

							//Determines how far text can go in the text box
							if (activeTextBox->text.findCharacterPos(activeTextBox->text.getString().getSize()).x < activeTextBox->txtBox.getPosition().x + 340) { 
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
						
						activeTextBox->text.setString(activeTextBox->leftText + activeTextBox->rightText);
						menu->drawWindow(MainWindow);
					}
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

