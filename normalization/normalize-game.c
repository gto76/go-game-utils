
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
	char *game;
	int retValue = checkArguments(argc, argv, &game);
 	if (retValue == EXIT_FAILURE) {
		return EXIT_FAILURE;
	}
	
	FILE * gameFile;
	gameFile = fopen(game, "r");
	if (gameFile == NULL) {
		fprintf(stderr, "normalize-game: Could not open file %s\n", game);
		return EXIT_FAILURE;
    }

	int boardSize = getBoardSize(gameFile);
	if (boardSize < 0) { //error
		fprintf(stderr, "normalize-game: Could not find board size in game file %s\n", game);
		return EXIT_FAILURE;
	} else {
		printf("%d\n", boardSize);
	}

	//int transformationsOut = findTransformations(move, boardSize, transformations);
	//printf("%d\n", transformationsOut);

	fclose(gameFile);
	return EXIT_SUCCESS;
}

int getBoardSize(FILE * gameFile) {
	char line[1000];
	while (fgets(line, 1000, gameFile) != NULL) {
		//printf("analizing line: %s", line);
		//fflush(stdout);
		char * sz = "SZ[";
		if (!strncmp(line, sz, 3)) {
			//printf("line holds board size info!\n");
			//fflush(stdout);
			char sizeString[3];
			int i;
			for (i = 0; i < 3; i++) {
				if (isdigit(line[3+i])) {
					sizeString[i] = line[3+i];
				} else {
					sizeString[i] = '\0';
					return atoi(sizeString);
				}
			}
		}
	}
	return -1;
}


// Checks if all arguments make sense, and asigns them to passed pointers.
int checkArguments(int argc, char **argv, char **game) {
	// No of arg check
	if (argc != 2) {
		fprintf(stderr, "normalize-game: There should be one argument\n");	
		return EXIT_FAILURE;
	} 
	*game = *(argv+1);
	return EXIT_SUCCESS;
}

