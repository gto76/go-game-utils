#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "argument-checker.h"
#include "util.h"

// Prints transformed move.
// Arguments:	1. string move ('ca' for first row, third column),
//				2. int board size ('9' for size of 9x9), 
//				3. int transformations (first three bits of int signify which of the three transformations gets executed on move).

int transformMove(char *move, int boardSize, int transformations, char *letters) {
	int x = getNumericX(move[0], boardSize);
	int y = getNumericY(move[1], boardSize);
	transformXY(&x, &y, transformations);
	getAlphabeticXY(x, y, boardSize, letters);
}

int transformXY(int* x, int* y, int transformations) {
	if (getTransformationBit(1, transformations)) {
		*x *= -1;
	}
	if (getTransformationBit(2, transformations)) {
		*y *= -1;
	}
	if (getTransformationBit(3, transformations)) {
		int tmp = *x;
		*x = *y;
		*y = tmp;
	}
}

