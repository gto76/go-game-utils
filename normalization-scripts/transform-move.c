#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "argument-checker.h"

// Prints transformed move.
// Arguments:	1. string move ('ca' for first row, third column),
//				2. int board size ('9' for size of 9x9), 
//				3. int transformations (first three bits of int signify which of the three transformations gets executed on move).

int getLetterCoordinates(int x, int y, char *letters);
int transformMove(char *letters);

char *move;
int boardSize;
int transformations;

int main(int argc, char **argv) {
	int retValue = checkArguments(argc, argv, &move, &boardSize, &transformations);
 	if (retValue == EXIT_FAILURE) {
		return EXIT_FAILURE;
	}
	
	char letterCoordinates[3];
	transformMove(letterCoordinates);
	printf("%s\n", letterCoordinates); 
	return EXIT_SUCCESS;
}

int coordinateNotInRange(char *c) {
	return *c < 97 || *c > 97 + boardSize-1;
}

int transformMove(char *letters) {
	int x = getX();
	int y = getY();
	if (transformation(1)) {
		x *= -1;
	}
	if (transformation(2)) {
		y *= -1;
	}
	if (transformation(3)) {
		int tmp = x;
		x = y;
		y = tmp;
	}
	getLetterCoordinates(x, y, letters);
}

// a=0, b=1, ... i=8, ...
int getX() {
	return move[0] - 97 - boardSize/2;
}

// a=0, b=1, ... i=8, ...
int getY() {
	return move[1] - 97 - boardSize/2;
}

// Is i-th bit of transformations int set?
int transformation(int i) {
	return (transformations >> (i-1)) & 1; 
}

// Transform back from number coordinates to letter ones.
int getLetterCoordinates(int x, int y, char *letters) {
	letters[0] = x + boardSize/2 + 97;
	letters[1] = y + boardSize/2 + 97;
	letters[2] = '\0';
}
