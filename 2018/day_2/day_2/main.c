#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define LINES 250
#define ARRAY_SIZE 28

void addCounters(char arr[], int *a, int *b);
int calcCheckSum(int a, int b);
void getCommonLetters(char letters[], char org[], char compare[]);
void printCommonLetters(char arr[]);

int main() {
	char words[LINES][ARRAY_SIZE];
	int line = 0;
	int two = 0;
	int three = 0;
	FILE *f;

	f = fopen("input.txt", "r");
	if (f == NULL) {
		printf("Unable to open file");
		return 1;
	}

	while (fgets(words[line++], sizeof words[line], f) != NULL);
	fclose(f);

	for (int i = 0; i < LINES; i++) {
		addCounters(words[i], &two, &three);
	}

	printf("%d\n", calcCheckSum(two, three));

	char commonLetters[ARRAY_SIZE];
	for (int i = 0; i < LINES; i++) {
		for (int j = 0; j < LINES; j++) {
			getCommonLetters(&commonLetters, words[i], words[j]);
		}
	}

	printCommonLetters(commonLetters);

	return 0;
}

void addCounters(char arr[], int *a, int *b) {
	int two = 0;
	int three = 0;
	int chars[ARRAY_SIZE] = { 0 };

	for (int i = 0; i < ARRAY_SIZE; i++) {
		if (arr[i] == '\n') break;
		chars[arr[i] - 97]++;
	}

	for (int i = 0; i < ARRAY_SIZE; i++) {
		if (arr[i] == '\n') break;

		if (!two && chars[i] == 2) {
			*a = *a + 1;
			two = 1;
		}

		if (!three && chars[i] == 3) {
			*b = *b + 1;
			three = 1;
		}

		if (two && three) break;
	}
}

int calcCheckSum(int a, int b) {
	return a * b;
}

void getCommonLetters(char letters[], char org[], char compare[]) {
	int commonCount = 0;
	int uncommonIndex = 0;

	for (int i = 0; i < ARRAY_SIZE; i++) {
		if (org[i] == compare[i]) {
			commonCount++;
		}
		else {
			uncommonIndex = i;
		}
	}

	if (commonCount == ARRAY_SIZE - 1) {
		int pos = 0;
		for (int j = 0; j < ARRAY_SIZE; j++) {
			if (j != uncommonIndex) {
				letters[pos++] = org[j];
			}
		}
	}
}

void printCommonLetters(char arr[]) {
	for (int i = 0; i < ARRAY_SIZE; i++) {
		if (arr[i] == '\n') return;
		printf("%c", arr[i]);
	}
}