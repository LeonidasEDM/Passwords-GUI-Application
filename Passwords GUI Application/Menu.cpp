#include "Menu.h"

File* file; //Object that hold file type while a file is open

void MainMenu::initObjects() {
	//Initialize Buttons
	initButton(225, 75, 345, 355, sf::Color::Black, 2, sf::Color::Cyan);
	initButton(225, 75, 345, 455, sf::Color::Black, 2, sf::Color::Cyan);

	//Initialize TextLabels
	bankaiFont.loadFromFile("Res/Fonts/bankai.otf");
	initLabel(290, 150, 50, "Password Manager", sf::Color::Cyan);
	initLabel(427, 375, 27, "Login", sf::Color::Cyan);
	initLabel(392, 477, 27, "New Account", sf::Color::Cyan);
}

void LoginMenu::initObjects() {
	//Initialize Buttons
	initButton(125, 50, 150, 555, sf::Color::Black, 2, sf::Color::Cyan);
	initButton(125, 50, 650, 555, sf::Color::Black, 2, sf::Color::Cyan);

	//Initialize TextLabels
	bankaiFont.loadFromFile("Res/Fonts/bankai.otf");
	initLabel(182, 562, 27, "Back", sf::Color::Cyan);
	initLabel(682, 562, 27, "Login", sf::Color::Cyan);
	initLabel(265, 225, 30, "Username", sf::Color::Cyan);
	initLabel(265, 330, 30, "Password", sf::Color::Cyan);

	//Initialize TextBoxxes
	initTextBox(350, 35, 267, 272, sf::Color(62, 70, 84, 255), 2, sf::Color(62, 70, 84, 255));
	initTextBox(350, 35, 267, 376, sf::Color(62, 70, 84, 255), 2, sf::Color(62, 70, 84, 255));
}

void UserMenu::initObjects() {
	//Initialize Buttons
	initButton(75, 25, 100, 605, sf::Color::Black, 2, sf::Color::Cyan);
	initButton(75, 25, 700, 605, sf::Color::Black, 2, sf::Color::Cyan);

	//Initialize TextLabels
	bankaiFont.loadFromFile("Res/Fonts/bankai.otf");
	initLabel(120, 605, 20, "Back", sf::Color::Cyan);
	initLabel(720, 605, 20, "Save", sf::Color::Cyan);

	//Initialize TextBoxxes
	for (int i = 1; i < 21; i++) {
		initTextBox(550, 18, 40, 28*i, sf::Color(32, 17, 65, 255), 2, sf::Color(32, 17, 65, 255));
	}
}

void Error::initObjects()
{
	//Initialize Buttons
	initButton(75, 25, 90, 135, sf::Color::Black, 2, sf::Color::Cyan);
	initButton(75, 25, 290, 135, sf::Color::Black, 2, sf::Color::Cyan);

	//Initialize TextLabels
	bankaiFont.loadFromFile("Res/Fonts/bankai.otf");
	initLabel(55, 50, 30, "Would You like to Save Changes?", sf::Color::Cyan);
	initLabel(110, 135, 20, "No", sf::Color::Cyan);
	initLabel(310, 135, 20, "Yes", sf::Color::Cyan);
}


void Menu::drawWindow(sf::RenderWindow* window)
{
	window->clear(sf::Color(32, 17, 65, 255));

	for (sf::RectangleShape* btn : listOfBtns) { //Draw Buttons
		window->draw(*btn);
	}

	for (sf::Text* txt : listOfLabels) { //Draw Labels
		window->draw(*txt);
	}

	for (int i = 0; i < listOfTextBoxxes.size(); i++) {
		window->draw(listOfTextBoxxes.at(i)->txtBox);
		window->draw(listOfTextBoxxes.at(i)->text);
		window->draw(listOfTextBoxxes.at(i)->cursor);
	}

	window->display();

}

void MainMenu::updateButtons(Menu*& currentMenu, int btn) {
	listOfBtns.clear();
	listOfLabels.clear();
	delete currentMenu;
	switch (btn) {
	case 0:
		currentMenu = new LoginMenu;
		
		break;
	case 1:
		currentMenu = new LoginMenu;
		break;
	}
	currentMenu->initObjects();
}

void LoginMenu::updateButtons(Menu*& currentMenu, int btn) {
	switch (btn) {
	case 0:
		listOfBtns.clear();
		listOfLabels.clear();
		delete currentMenu;
		currentMenu = new MainMenu;
		currentMenu->initObjects();
		break;
	case 1:
		switch (login())
		{
		case true:
			file->openSavedFile(currentMenu);
		}
		break;
	}
}

void UserMenu::updateButtons(Menu*& currentMenu, int btn) {
	switch (btn) {
	case 1:
		saveChanges(currentMenu);
	}

	userMenuOpen = false;
	listOfBtns.clear();
	listOfLabels.clear();
	listOfTextBoxxes.clear();
	delete currentMenu;
	currentMenu = new MainMenu;
	currentMenu->initObjects();

}

void Error::updateButtons(Menu*& currentMenu, int btn)
{
	switch (btn) {
	case 0:
		fileUpdate = false;
		break;
	case 1:
		fileUpdate = false;
		saveChanges(currentMenu);
		break;
		}

	userMenuOpen = false;
	listOfBtns.clear();
	listOfLabels.clear();
	listOfTextBoxxes.clear();
	delete currentMenu;
	currentMenu = new MainMenu;
	currentMenu->initObjects();
}

void Menu::initButton(int length, int height, int x, int y, sf::Color fillColor, int outlineThickness, sf::Color outlineColor) {
	sf::RectangleShape* btn = new sf::RectangleShape;
	btn->setSize(sf::Vector2f(length, height));
	btn->setPosition(x, y);
	btn->setFillColor(fillColor);
	btn->setOutlineThickness(outlineThickness);
	btn->setOutlineColor(outlineColor);
	listOfBtns.emplace_back(btn);
}

void Menu::initLabel(int x, int y, int charSize, std::string text, sf::Color fillColor) {
	sf::Text* txt = new sf::Text;
	txt->setPosition(x, y);
	txt->setCharacterSize(charSize);
	txt->setString(text);
	txt->setFillColor(fillColor);
	txt->setFont(bankaiFont);
	listOfLabels.emplace_back(txt);
}

void Menu::initTextBox(int length, int height, int x, int y, sf::Color fillColor, int outlineThickness, sf::Color outlineColor) {
	
	TextBox* Box = new TextBox;
	Box->txtBox.setSize(sf::Vector2f(length, height));
	Box->txtBox.setPosition(x, y);
	Box->txtBox.setFillColor(fillColor);
	Box->txtBox.setOutlineThickness(outlineThickness);
	Box->txtBox.setOutlineColor(outlineColor);
	listOfTextBoxxes.emplace_back(Box);

	Box->text.setPosition(x+3, y-(height/7));
	Box->text.setFont(bankaiFont);
	Box->text.setCharacterSize(height);
	Box->text.setFillColor(sf::Color::White);

	Box->cursor.setSize(sf::Vector2f(3, height));
	Box->cursor.setPosition(x, y);
	Box->cursor.setFillColor(sf::Color(255,255,255,0));
}

bool LoginMenu::login() {

	std::string userName = listOfTextBoxxes.at(0)->text.getString();
	std::string password = listOfTextBoxxes.at(1)->text.getString();

	readFile = new std::ifstream; //Create Read Access for a file
	
		readFile->open(userName + ".txt"); //Attempt to open file
		
			if (readFile->is_open()) { //If the file exists, File is Open
				std::cout << "Open";
				std::string output;
				std::getline(*readFile, output);
				if (password == output) {
					readFile->close();
					return true;
				}
			}
			else { //If file does not exist, try input again
				std::cout << "Don't exist";
			}
			
}

void LoginMenu::enterButtonPressed(Menu*& currentMenu) {
	switch (login())
	{
	case true:
		file->openSavedFile(currentMenu);
		break;
	}
}

void UserMenu::enterButtonPressed(Menu*& currentMenu) {

}

void Error::enterButtonPressed(Menu*& currentMenu)
{

}

void File::openSavedFile(Menu*& currentMenu)
{
	std::string* temp = nullptr;
	temp = new std::string; //holds name of file after clearing all lists
	*temp = currentMenu->listOfTextBoxxes.at(0)->text.getString();
	currentMenu->listOfBtns.clear();
	currentMenu->listOfLabels.clear();
	currentMenu->listOfTextBoxxes.clear();
	delete currentMenu;
	currentMenu = new UserMenu;
	currentMenu->initObjects();
	file = new File(*temp);
	delete temp;
	file->getLines(currentMenu);
	currentMenu->userMenuOpen = true;
}

void File::getLines(Menu*& currentMenu)
{	
	std::string output;
	savedFile->open(fileName);

	std::getline(*savedFile, output); //Required Iteration (Security)

	while (!savedFile->eof()) {
		std::getline(*savedFile,output);
		currentMenu->listOfTextBoxxes.at(lines)->leftText = output;
		currentMenu->listOfTextBoxxes.at(lines)->text.setString(currentMenu->listOfTextBoxxes.at(lines)->leftText);
		lines++;
	}
	savedFile->close();
}

void Menu::saveChanges(Menu*& menu) {
		std::string text;
		fileUpdate = false;
		file->readFile = new std::ifstream;
		file->writeFile = new std::ofstream;

		file->readFile->open(file->fileName);
		std::getline(*file->readFile, *file->Pw);
		file->readFile->close();

		file->writeFile->open(file->fileName);
		file->writeFile->clear();
		*file->writeFile << *file->Pw;

		int count = 0;
		while (count != menu->listOfTextBoxxes.size()) {
			text = menu->listOfTextBoxxes.at(count)->text.getString();
			*file->writeFile << "\n" << text;
			count++;
		}
		file->writeFile->close();
}
