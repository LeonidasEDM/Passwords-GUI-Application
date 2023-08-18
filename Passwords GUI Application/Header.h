#pragma once
char keyCode_Letters[26] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm','n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z' };
char keyCode_SLetters[26] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M','N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z' };
char keyCode_Numbers[10] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };
char keyCode_SNumbers[10] = { ')', '!', '@', '#', '$', '%', '^', '&', '*', '(' };
char keyCode_Symbols[11] = { '[',']',';',',','.','\'','/','(\)','`','=','-' };
char keyCode_SSymbols[11] = { '{','}',':','<','>','"','?','|','~','+','_' };
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