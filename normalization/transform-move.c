#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "argument-checker.h"
#include "util.h"

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

////////////////////////////////////

int transformMove(char *letters) {
	int x = getNumericX(move[0], boardSize);
	int y = getNumericY(move[1], boardSize);
	if (getTransformationBit(1, transformations)) {
		x *= -1;
	}
	if (getTransformationBit(2, transformations)) {
		y *= -1;
	}
	if (getTransformationBit(3, transformations)) {
		int tmp = x;
		x = y;
		y = tmp;
	}
	getAlphabeticXY(x, y, boardSize, letters);
}

// Transform back from number coordinates to letter ones.
//int getLetterCoordinates(int x, int y, char *letters) {
//	letters[0] = x + boardSize/2 + 97;
//	letters[1] = y + boardSize/2 + 97;
//	letters[2] = '\0';
//}
