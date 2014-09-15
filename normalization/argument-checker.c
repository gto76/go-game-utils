#include <stdio.h>
#include <stdlib.h>

// Checks if all arguments make sense, and asigns them to passed pointers.

int checkArguments(int argc, char **argv, char **move, int *boardSize, int *transformations, char *functionName) {
	// No of arg check
	if (argc != 4) {
		fprintf(stderr, "%s: there should be three arguments\n", *functionName);	
		return EXIT_FAILURE;
	} 
	// Board size check
	char *boardSizeString = *(argv+2);
	*boardSize = atoi(boardSizeString);
	if (*boardSize < 2 || *boardSize > 25 || *boardSize%2 == 0) {
		fprintf(stderr, "%s: invalid board size argument: %s\n", *functionName, boardSizeString);	
		return EXIT_FAILURE;
	}
	// Move check
	*move = *(argv+1);
	//printf("1 %s\n", *(argv+1)); OK
	if (strlen(*move) != 2 || coordinateNotInRange(*move, *boardSize) || coordinateNotInRange(*move+1, *boardSize) ) {
		fprintf(stderr, "%s: invalid move argument: %c\n", *functionName, *move);	
		return EXIT_FAILURE;
	}
	// Transformations check
	char *transformationsString = *(argv+3);
	*transformations = atoi(transformationsString);
	if (*transformations < 0) {
		fprintf(stderr, "%s: invalid transformations argument: %s\n", *functionName, transformationsString);	
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

int coordinateNotInRange(char *c, int boardSize) {
	return *c < 97 || *c > 97 + boardSize-1;
}

