
#include <stdio.h>
#include <stdlib.h>

#include "find-transformations.h"

int main(int argc, char **argv) {
	// 1.Use first argument as games filename.
	char *game;
	int retValue = checkArguments(argc, argv, &game);
 	if (retValue == EXIT_FAILURE) {
		return EXIT_FAILURE;
	}
	// 2.Open game file.
	FILE * gameFile;
	gameFile = fopen(game, "r");
	if (gameFile == NULL) {
		fprintf(stderr, "normalize-game: Could not open file %s\n", game);
		return EXIT_FAILURE;
	}
	fprintf(stderr, "normalize-game: Normalizing game: %s\n", game);
	// 3.Get board size.
	int boardSize = getBoardSize(gameFile);
	if (boardSize < 0) { //error
		fprintf(stderr, "normalize-game: Could not find board size in game file %s\n", game);
		return EXIT_FAILURE;
	} 
	fprintf(stderr, "normalize-game: Board size: %d\n", boardSize);
	// 4.Find necesary trasformations for game to be normalized.
	// TODO: Manage errors in more detail.
	int transformations = getTransformations(gameFile, boardSize);  
	if (transformations == -99) {
		printf("normalize-game: File contains no moves.\n");
		transformations = 0;
	} else if (transformations < 0) {
		fprintf(stderr, "normalize-game: Serious error occured when reading game file: %d\n", transformations);
		return EXIT_FAILURE;
	}
	fprintf(stderr, "normalize-game: Transformations: %d\n", transformations);
	// 4.Transform game using transformations, and print it to stdout.
	transformAndPrintGame(gameFile, boardSize, transformations);	
	// 5.Close file and exit.
	fclose(gameFile);
	return EXIT_SUCCESS;
}

int transformAndPrintGame(FILE * gameFile, int boardSize, int transformations) {
	rewind(gameFile);
	char line[1000];
	char move[3];
	while (fgets(line, 1000, gameFile) != NULL) {
		// If line contains a move, get the move,
		if (!getMoveFromLine2(line, move, boardSize)) {
			// transform it,
			char transformedMove[3];			
			transformMove(move, boardSize, transformations, transformedMove);
			// and print the line with transformed move,
			printLineWithTransformedMove(line, transformedMove);
		}
		// otherwise just print the line.
		else {
			printf("%s", line);
		}
	}
}

// Returns 0 if finds move and asigns it to move, othervise negative value
int getMoveFromLine2(char * line, char * move, int boardSize) {
	// TODO: devide corupt file errors and only messages
	if (strlen(line) < 6) { 
		return -1; // line to short to contain move
	}
	char * szB = ";B[";
	char * szW = ";W[";
	if (strncmp(line, szB, 3) && strncmp(line, szW, 3)) {
		return -2; // first three characters do not conform to the move convention
	}
	if (line[5] != ']') {
		return -3; // something wrong with the move
	}
	if (line[3] < 97 || line [3] > 97 + boardSize-1) {
		return -4; // first coordinate is out of range 
	}
	if (line[4] < 97 || line [4] > 97 + boardSize-1) {
		return -5; // second coordinate is out of range
	}
	move[0] = line[3];
	move[1] = line[4];
	move[2] = '\0';
	return 0;
}

int printLineWithTransformedMove(char * line, char * transformedMove) {
	printf("%c%c%c%c%c%c\n", line[0], line[1], line[2], transformedMove[0], transformedMove[1], line[5]);
}

int getTransformations(FILE * gameFile, int boardSize) {
	int transformations = 0;
	char nextMove[3];
	int status = getNextMove(gameFile, nextMove);
	if (status == -99) {
		return status; // Could not find any moves
	}
	// If all transformations freeze bits (bits 4 to 6) have been set then break.
	while (transformations < 55) {
		transformations = findTransformations(nextMove, boardSize, transformations);
		status = getNextMove(gameFile, nextMove);
		if (status != 0) {
			return status;
		}
	}
	return transformations;
}

int getNextMove(FILE * gameFile, char * nextMove) {
	char line[1000];
	int status = -99;
	while (fgets(line, 1000, gameFile) != NULL) {
		char * szB = ";B[";
		char * szW = ";W[";
		if (!strncmp(line, szB, 3) || !strncmp(line, szW, 3)) {
			status = getMoveFromLine(line, nextMove);
			if (status == 0) {
				return 0; // If getMoveFromLine executed correctly return, else keep scaning lines
			}
		}
	}
	return status; // If ececution comes to here, function couldnt find any more moves.
	// TODO: this is not necesaryly an error, game could finish with resignation after two moves for instance.
	// passi ( ;W[] ) se ne smejo izgubit, preveri tudi skripto!!!!
}

int getMoveFromLine(char * line, char * nextMove) {
	char * moveStart = strchr(line , '[');
	char * moveEnd = strchr(line , ']');
	if (moveStart == NULL || moveEnd == NULL) {
		return -1;
	}
	int moveLength = moveEnd - moveStart -1;
	if (moveLength != 2) { 
		return -2;
	}
	nextMove[0] = *(moveStart+1);
	nextMove[1] = *(moveStart+2);
	nextMove[2] = '\0';

	return 0;
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

