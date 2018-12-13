#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define ARRAY_SIZE 22
#define X 1000
#define Y 1000

void getId(char arr[], int *id, int *pos);
void getXY(char arr[], int *x, int *y, int *pos);
void getWH(char arr[], int *w, int *h, int *pos);

int main() {
	char area[X][Y] = {'.'};

	FILE *f;

	f = fopen("input.txt", "r");
	if (f == NULL) {
		printf("Unable to open file");
		return 1;
	}

	char line[ARRAY_SIZE];
	while (fgets(line, sizeof line, f) != NULL) {
		int id = 0;
		int pos = 0;
		int x = 0;
		int y = 0;
		int w = 0;
		int h = 0;
		getId(line, &id, &pos);
		getXY(line, &x, &y, &pos);
		getWH(line, &w, &h, &pos);

		// #56 @ 152,610: 17x16
		printf("#%d @ %d,%d: %dx%d\n", id, x, y, w, h);
	}

	fclose(f);
	return 0;
}

void getId(char arr[], int *id, int *pos) {
	for (int i = 0; i < ARRAY_SIZE; i++) {
		if (arr[i] == '#') {
			for (int j = i + 1; j < ARRAY_SIZE; j++) {
				if (arr[j] == ' ') {
					*pos = j;
					return;
				}
				else {
					*id = *id * 10 + (arr[j] - 48);
				}
			}
		}
	}
}

void getXY(char arr[], int *x, int *y, int *pos) {
	int separate = 0;

	// bypas 3 chars
	for (int i = *pos + 3; i < ARRAY_SIZE; i++) {
		if (arr[i] == ',') {
			separate = 1;
		}
		else if (arr[i] == ':') {
			*pos = i;
			return;
		}
		else if (!separate) {
			*x = *x * 10 + (arr[i] - 48);
		}
		else if (separate) {
			*y = *y * 10 + (arr[i] - 48);
		}
	}
}

void getWH(char arr[], int *w, int *h, int *pos) {
	int separate = 0;

	// bypas 2 chars
	for (int i = *pos + 2; i < ARRAY_SIZE; i++) {
		if (arr[i] == 'x') {
			separate = 1;
		}
		else if (arr[i] == '\n') {
			*pos = i;
			return;
		}
		else if (!separate) {
			*w = *w * 10 + (arr[i] - 48);
		}
		else if (separate) {
			*h = *h * 10 + (arr[i] - 48);
		}
	}
}