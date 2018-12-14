#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define ARRAY_SIZE 30
#define X 1008
#define Y 1008

void setPoints(char arr[], char area[][Y], long *covered);
void getId(char arr[], int *id, int *pos);
void getXY(char arr[], int *x, int *y, int *pos);
void getWH(char arr[], int *w, int *h, int *pos);
long countX(char arr[][Y]);
void printArea(char arr[][Y]);

int main() {
	char area[X][Y];
	for (int i = 0; i < X; i++)
		for (int j = 0; j < Y; j++)
			area[i][j] = '.';

	long covered = 0;
	FILE *f;

	// load input_test to test; area 8x8
	f = fopen("input.txt", "r");
	if (f == NULL) {
		printf("Unable to open file");
		return 1;
	}

	char line[ARRAY_SIZE];
	while (fgets(line, sizeof line, f) != NULL) setPoints(line, area, &covered);

	fclose(f);

	//printArea(area);
	printf("\n\nCount of X: %d\n", countX(area));
	printf("Count of sum X: %d", covered);

	return 0;
}

void setPoints(char arr[], char area[][Y], long *covered) {
	int id = 0;
	int pos = 0;
	int x = 0;
	int y = 0;
	int w = 0;
	int h = 0;
	getId(arr, &id, &pos);
	getXY(arr, &x, &y, &pos);
	getWH(arr, &w, &h, &pos);
	printf("#%d @ %d,%d: %dx%d\n", id, x, y, w, h);

	for (int i = y; i < w + y; i++) {
		for (int j = x; j < h + x; j++) {
			if (area[i][j] == '.') {
				area[i][j] = id + '0';
			}
			else {
				area[i][j] = 'X';
				*covered = *covered + 1;
			}
		}
	}
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

long countX(char arr[][Y]) {
	long x = 0;
	for (int i = 0; i < X; i++) {
		for (int j = 0; j < Y; j++) {
			if (arr[i][j] == 'X') x++;
		}
	}

	return x;
}

void printArea(char arr[][Y]) {
	int x = 0;
	for (int i = 0; i < X; i++) {
		for (int j = 0; j < Y; j++) {
			printf("%c", arr[i][j]);
		}
		printf("\n");
	}
}