#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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
	// No of arg check
	if (argc != 4) {
		fprintf(stderr, "transform-move: there should be three arguments\n");	
		return EXIT_FAILURE;
	} 
	// Board size check
	char *boardSizeString = *(argv+2);
	boardSize = atoi(boardSizeString);
	if (boardSize < 2 || boardSize > 25 || boardSize%2 == 0) {
		fprintf(stderr, "transform-move: invalid board size argument: %s\n", boardSizeString);	
		return EXIT_FAILURE;
	}
	// Move check
	move = *(argv+1);
	//printf("1 %s\n", *(argv+1)); OK
	if (strlen(move) != 2 || coordinateNotInRange(move) || coordinateNotInRange(move+1) ) {
		fprintf(stderr, "transform-move: invalid move argument: %s\n", move);	
		return EXIT_FAILURE;
	}
	// Transformations check
	char *transformationsString = *(argv+3);
	transformations = atoi(transformationsString);
	if (transformations < 0) {
		fprintf(stderr, "transform-move: invalid transformations argument: %s\n", transformationsString);	
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
	//return transformations % (int) pow((double) 2, (double) (i-1));
	return (transformations >> (i-1)) & 1; 
}

// Transform back from number coordinates to letter ones.
int getLetterCoordinates(int x, int y, char *letters) {
	letters[0] = x + boardSize/2 + 97;
	letters[1] = y + boardSize/2 + 97;
	letters[2] = '\0';
	/*const char letterCoordinates[] = {
		x + boardSize/2 + 97,
		y + boardSize/2 + 97,
	};*/
	
	//const char letterCoordinates = { 100, 100, '\0' }; //BAD
	//const char *letterCoordinates = "ss"; //OK
	//return &letterCoordinates;
}
