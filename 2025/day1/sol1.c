#include <stdio.h>
#include <stdlib.h>

int rotate(char dir, int clicks, int pos);

int main(int argc, char* argv[]) {
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

	int solution = 0;

	char first_operation[10];
	char first_dir;
	int first_clicks;
	fgets(first_operation, 10, input_file);

	sscanf(first_operation, "%c%d", &first_dir, &first_clicks);

	int current_pos = 50;
	int new_pos = rotate(first_dir, first_clicks, 50);

	if (new_pos == 0) solution++;

	current_pos = new_pos;

	char dir;
	int clicks;

	while (fscanf(input_file, " %c%d", &dir, &clicks) != EOF) {
		new_pos = rotate(dir, clicks, current_pos);
		if (new_pos == 0) solution++;
		current_pos = new_pos;
	}

	printf("Solution: %d\n", solution);

	fclose(input_file);
	return 0;
}

int rotate(char dir, int clicks, int pos) {
	if (dir == 'L') {
		return (pos+clicks) % 100;
	}
	else {
		return (pos-clicks + 100) % 100;
	}
}
