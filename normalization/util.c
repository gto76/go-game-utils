
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

// Gets numerical coordinate from char one.
// If board size = 9x9 then a=-4, b=-3, ... i=4.
int getNumericalCoordinate(char c, int boardSize) {
	return c - 97 - boardSize/2;
}
