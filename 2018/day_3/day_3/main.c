#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define ARRAY_SIZE 30
#define X 1005
#define Y 1005
#define OV_SIZE 2000

void setPoints(char arr[], int area[], int ov[]);
void getId(char arr[], int *id, int *pos);
void getXY(char arr[], int *x, int *y, int *pos);
void getWH(char arr[], int *w, int *h, int *pos);
long countX(int arr[]);
void printArea(int arr[]);
int searchUncovered(int arr[]);

int main() {
	int *area = malloc(X * Y * sizeof(int));

	int overlap[OV_SIZE];
	for (int i = 0; i < X; i++) {
		for (int j = 0; j < Y; j++) {
			area[i * X + j] = 0;
		}
	}

	long covered = 0;
	FILE *f;

	f = fopen("input3.txt", "r");
	if (f == NULL) {
		printf("Unable to open file");
		return 1;
	}

	char line[ARRAY_SIZE];
	int row = 0;
	while (fgets(line, sizeof line, f) != NULL) {
		row++;
		setPoints(line, area, overlap);
	}

	fclose(f);

	for (int i = 0; i < X; i++) free(area[i]);

	//printArea(area);
	printf("\n\nPart 1: %d\n", countX(area));
	printf("Part 2: %d\n", searchUncovered(overlap));

	return 0;
}

void setPoints(char arr[], int area[], int ov[]) {
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

	ov[id - 1] = id;

	for (int i = x; i < w + x; i++) {
		for (int j = y; j < h + y; j++) {
			if (area[i * X + j] == 0) {
				area[i * X + j] = id;
			}
			else {
				ov[id - 1] = 0;
				ov[area[i * X + j] - 1] = 0;
				area[i * X + j] = -1;
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

long countX(int arr[]) {
	long x = 0;
	for (int i = 0; i < X; i++) {
		for (int j = 0; j < Y; j++) {
			if (arr[i * X + j] == -1) x++;
		}
	}

	return x;
}

void printArea(int arr[]) {
	int x = 0;
	for (int i = 0; i < X; i++) {
		for (int j = 0; j < Y; j++) {
			printf("%d", arr[i * X + j]);
		}
		printf("\n");
	}
}

int searchUncovered(int arr[]) {
	for (int i = 0; i < X; i++) {
		if (arr[i] != 0) return arr[i];
	}

	return 0;
}