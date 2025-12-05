/*********************************************************************************************************
*
*	Kristaq Vincani, 1/12/25
*	File: day1/sol2.c
*
*	This program solves part #2 of https://adventofcode.com/2025/day/1
*
*********************************************************************************************************/

#include <stdio.h> // printf, fprintf, fscanf
#include <stdlib.h> // FILE, fopen, fclose

/* main solver function prototype */
int rotate_and_count(char dir, int clicks, int* pos);

/* program entry point */
int main(int argc, char* argv[]) {
	
	/* no file specified */
	if (argc < 2) {
		fprintf(stderr, "No file provided!\n");
		return 1;
	}

	FILE* input_file;

	input_file = fopen(argv[1], "r");
	if (input_file == NULL) {
		fprintf(stderr, "The file does not exist!\n");
		return 1;
	}

	int solution = 0; // total amount the needle landed on 0 and passed through it after a rotation for each rotation in the input file

	char dir; // 'L' for left and 'R' for right
	int clicks; // amount of clicks performed in the given direction
	int current_pos = 50; // we start at position 50, as specified in the problem
	
	/* read the input file until it ends */
	while (fscanf(input_file, " %c%d", &dir, &clicks) != EOF) {
		solution += rotate_and_count(dir, clicks, &current_pos); // rotate and count for each rotation in the file
	}
	
	printf("Solution: %d\n", solution);

	fclose(input_file);
	return 0;
}

/*
	Our solution essentially performs each step manually and checks if it' zero
	The wrap-around logic is the same as part 1
	We use a pointer for pos to store it's position for the next rotation
*/
int rotate_and_count(char dir, int clicks, int* pos) {
	int zeroes = 0;
	for (int i = 0; i < clicks; i++) {
		if (dir == 'L') {
			*pos = (*pos - 1 + 100) % 100;
		}
		else *pos = (*pos + 1) % 100;
		
		if (*pos == 0) zeroes++;
	}
	return zeroes;
}
