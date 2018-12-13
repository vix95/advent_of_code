#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define ARRAY_SIZE 10

int main() {
	int freq = 0;
	FILE *f;

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
	}

	fclose(f);
	printf("%d", freq);
	return 0;
}