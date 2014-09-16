// Utility functions for go game transformations

// Is i-th bit of transformations int set?
int getTransformationBit(int i, int transformations) {
	return (transformations >> (i-1)) & 1; 
}

int setTransformationBit(int i, int *transformations) {
	*transformations = *transformations | (1 << (i-1));
}

int unsetTransformationBit(int i, int *transformations) {
	*transformations = *transformations & ~(1 << (i-1));
}

// Gets numerical x coordinate from char.
// If board size = 9x9 then a=-4, b=-3, ... i=4.
int getNumericX(char c, int boardSize) {
	return (c - 97) - boardSize/2;
}

// Gets numerical y coordinate from one.
// If board size = 9x9 then a=4, b=3, ... i=-4.
int getNumericY(char c, int boardSize) {
	return boardSize/2 - (c - 97);
}

int getAlphabeticX(int i, int boardSize) {
	return (i + 97) + boardSize/2;
}

int getAlphabeticY(int i, int boardSize) {
	//return boardSize/2 + (i + 97);
	return 97 + boardSize/2 - i;
}

int getAlphabeticXY(int x, int y, int boardSize, char *letters) {
	letters[0] = getAlphabeticX(x, boardSize);
	letters[1] = getAlphabeticY(y, boardSize);
	letters[2] = '\0';
}

int getNumericCoordinateFromIndex(int i, int boardSize) {
	return i - boardSize/2;
}

int getAlphabeticXYFromIndexes(int i, int j, int boardSize, char *letters) {
	int x = getNumericCoordinateFromIndex(j, boardSize);
	int y = getNumericCoordinateFromIndex(i, boardSize);
	getAlphabeticXY(x, y, boardSize, letters);
}

