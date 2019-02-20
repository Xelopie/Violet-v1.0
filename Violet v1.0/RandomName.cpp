#include "stdafx.h"

char* RANDOMNAME::Generator() {
	/* Generate a random name for the cheat */
	srand(time(NULL));

	/* Generate a random length for the window's name */
	int length = rand() % 15 + 6;

	/* Allocate space for this random name */
	char* randomName = new char[length];

	/* Loop for generating name */
	for (int i = 0; i < length; i++) {
		int randomNum = rand() % 10 + 48;
		int randomBigChar = rand() % 26 + 65;
		int randomSmallChar = rand() % 26 + 97;
		int randomSelector = rand() % 3 + 1;

		switch (randomSelector) {
		case(1):
			randomName[i] = randomNum;
			break;
		case(2):
			randomName[i] = randomBigChar;
			break;
		case(3):
			randomName[i] = randomSmallChar;
			break;
		default:
			randomName[i] = 'a';
		}
	}

	/* Set the last character to be the null-character */
	randomName[length - 1] = '\0';
	
	return randomName;
}