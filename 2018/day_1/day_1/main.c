#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define ARRAY_SIZE 30
#define LINES 1001
#define TIMESFREQ 200

long searchTwice(long arr[], long pos, long num);

int main() {
	long freq = 0;
	long freq_ones = 0;
	long freqArr[LINES * TIMESFREQ];
	long row = 0;
	long twice = 0;
	FILE *f;

	for (int times = 0; times < TIMESFREQ; times++) {
		printf("iteration: %d\n", times);

		// input.txt; input2.txt
		f = fopen("input.txt", "r");
		if (f == NULL) {
			printf("Unable to open file");
			return 1;
		}

		char line[ARRAY_SIZE];
		while (fgets(line, sizeof line, f) != NULL) {
			long num = 0;

			for (int i = 1; i < ARRAY_SIZE; i++) {
				if (line[i] == '\n' || line[i] == '\0') break;
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

int searchTwice(long arr[], long pos, long num) {
	for (long i = 0; i < LINES * TIMESFREQ; i++) {
		if (i != pos) {
			if (arr[i] == num) return num;
		}
	}

	return 0;
}