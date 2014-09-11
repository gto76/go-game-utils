#include <stdio.h>
#include <stdlib.h>

// Checks if all arguments make sense, and asigns them to passed pointers.

int checkArguments(int argc, char **argv, char **move, int *boardSize, int *transformations) {
	// No of arg check
	if (argc != 4) {
		fprintf(stderr, "transform-move: there should be three arguments\n");	
		return EXIT_FAILURE;
	} 
	// Board size check
	char *boardSizeString = *(argv+2);
	*boardSize = atoi(boardSizeString);
	if (*boardSize < 2 || *boardSize > 25 || *boardSize%2 == 0) {
		fprintf(stderr, "transform-move: invalid board size argument: %s\n", boardSizeString);	
		return EXIT_FAILURE;
	}
	// Move check
	*move = *(argv+1);
	//printf("1 %s\n", *(argv+1)); OK
	if (strlen(*move) != 2 || coordinateNotInRange(*move) || coordinateNotInRange(*move+1) ) {
		fprintf(stderr, "transform-move: invalid move argument: %s\n", *move);	
		return EXIT_FAILURE;
	}
	// Transformations check
	char *transformationsString = *(argv+3);
	*transformations = atoi(transformationsString);
	if (*transformations < 0) {
		fprintf(stderr, "transform-move: invalid transformations argument: %s\n", transformationsString);	
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
