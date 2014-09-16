#include <stdio.h>
#include <stdlib.h>
#include "find-transformations.h"
#include "util.h"

#define SIZE 9

const char* results[][SIZE] = {							
//              -4		  -3        -2        -1         0         1         2         3         4	
/*  4 */	{"011001", "111101", "111101", "111101", "110100", "111100", "111100", "111100", "011000"},	
/*  3 */	{"111001", "011001", "111101", "111101", "110100", "111100", "111100", "011000", "111000"},
/*  2 */	{"111001", "111001", "011001", "111101", "110100", "111100", "011000", "111000", "111000"},
/*  1 */	{"111001", "111001", "111001", "011001", "110100", "011000", "111000", "111000", "111000"},
/*  0 */	{"101001", "101001", "101001", "101001", "000000", "101000", "101000", "101000", "101000"},
/* -1 */	{"111011", "111011", "111011", "011011", "110110", "011010", "111010", "111010", "111010"},
/* -2 */	{"111011", "111011", "011011", "111111", "110110", "111110", "011010", "111010", "111010"},
/* -3 */	{"111011", "011011", "111111", "111111", "110110", "111110", "111110", "011010", "111010"},
/* -4 */	{"011011", "111111", "111111", "111111", "110110", "111110", "111110", "111110", "011010"}
};

int main() {
	printf("Testing findTransformations function, for all positions on a 9x9 borard with no predefined transformations.\n");
	int i, j;
	int areTheSame = 1;
	printf("EXPECTED VALUES:\n");
	for (i = 0; i < SIZE; i++) {
		for (j = 0; j < SIZE; j++) {
			long int decimalNo = strtol(results[i][j], 0, 2);
			printf("%d\t", decimalNo); 
		}
		printf("\n");
	}

	printf("ACTUAL VALUES:\n");
	for (i = 0; i < SIZE; i++) {
		for (j = 0; j < SIZE; j++) {
			char letters[3];
			getAlphabeticXYFromIndexes(i, j, 9, letters);
			long int decimalNo = findTransformations(letters, 9, 0);
			printf("%d\t", decimalNo); 

			long int decimalNoFromTable = strtol(results[i][j], 0, 2);
			if (decimalNoFromTable != decimalNo) {
				areTheSame = 0;
			}
		}
		printf("\n");
	}

	if (areTheSame) {
		printf("TEST PASSED! All the values are the same.\n"); 
	} else {
		printf("TEST FAILED! Some values are not the same.\n"); 
	}

}
