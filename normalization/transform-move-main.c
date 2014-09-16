#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "argument-checker.h"
#include "util.h"
#include "transform-move.h"

// Prints transformed move.
// Arguments:	1. string move ('ca' for first row, third column),
//				2. int board size ('9' for size of 9x9), 
//				3. int transformations (first three bits of int signify which of the three transformations gets executed on move).

int main(int argc, char **argv) {
	char *move;
	int boardSize;
	int transformations;
	int retValue = checkArguments(argc, argv, &move, &boardSize, &transformations);
 	if (retValue == EXIT_FAILURE) {
		return EXIT_FAILURE;
	}
	
	char letterCoordinates[3];
	transformMove(move, boardSize, transformations, letterCoordinates);
	printf("%s\n", letterCoordinates); 
	return EXIT_SUCCESS;
}

