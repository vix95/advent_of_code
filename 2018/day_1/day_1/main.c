#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define ARRAY_SIZE 10
#define LINES 1001
#define TIMESFREQ 200

int searchTwice(int arr[], int pos, int num);

int main() {
	int freq = 0;
	int freq_ones = 0;
	int freqArr[LINES * TIMESFREQ];
	int row = 0;
	int twice = 0;
	FILE *f;

	for (int times = 0; times < TIMESFREQ; times++) {
		printf("iteration: %d\n", times);
		f = fopen("input.txt", "r");
		if (f == NULL) {
			printf("Unable to open file");
			return 1;
		}

		char line[ARRAY_SIZE];
		while (fgets(line, sizeof line, f) != NULL) {
			int num = 0;
			for (int i = 1; i < ARRAY_SIZE; i++) {
				if (line[i] == '\n') break;
				num = num * 10 + (line[i] - 48);
			}

			if (line[0] == '+') freq += num;
			if (line[0] == '-') freq -= num;

			freqArr[row] = freq;
			twice = searchTwice(freqArr, row, freq);
			//printf("part 2 times %d row %d: %d\n", times, row, freq);
			row++;
			if (twice != 0) break;
		}

		fclose(f);

		if (twice != 0) break;
		if (!times) freq_ones = freq;
	}

	printf("\npart 1: %d\n", freq_ones);
	printf("part 2: %d", twice);
	return 0;
}

int searchTwice(int arr[], int pos, int num) {
	for (int i = 0; i < LINES * TIMESFREQ; i++) {
		if (i != pos) {
			if (arr[i] == num) return num;
		}
	}

	return 0;
}