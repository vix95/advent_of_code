#include <iostream>
#include <fstream>
using namespace std;

const int LINES = 250;
const int ARRAY_SIZE = 26;

void addCounters(int arr1[], char arr2[][ARRAY_SIZE], int &a, int &b);
int calcCheckSum(int a, int b);
void getCommonLetters(char letters[], char words[][ARRAY_SIZE]);
void printCommonLetters(char arr[]);

int main() {
	int letters[ARRAY_SIZE] = { 0 };
	char words[LINES][ARRAY_SIZE] = {};
	int line = 0;
	int two = 0;
	int three = 0;
	fstream f;

	f.open("input.txt");
	if (!f) {
		cout << "Unable to open file";
		cin.get();
		exit(1);
	}

	while (!f.eof()) {
		int i = 0;
		char c;

		f.get(c);
		while (c != '\n') {
			words[line][i] = c;
			i++;
			f.get(c);
		}

		line++;
	}

	f.close();

	addCounters(letters, words, two, three);
	cout << calcCheckSum(two, three) << endl;

	char commonLetters[ARRAY_SIZE] = {};
	getCommonLetters(commonLetters, words);
	printCommonLetters(commonLetters);

	cin.get();
	return 0;
}

void addCounters(int arr1[], char arr2[][ARRAY_SIZE], int &a, int &b) {
	for (int i = 0; i < LINES; i++) {
		bool two = false;
		bool three = false;
		int chars[ARRAY_SIZE] = { 0 };

		for (int j = 0; j < ARRAY_SIZE; j++) {
			chars[arr2[i][j] - 97]++;
		}

		for (int j = 0; j < ARRAY_SIZE; j++) {
			if (!two && chars[j] == 2) {
				arr1[j]++;
				a++;
				two = true;
			}

			if (!three && chars[j] == 3) {
				arr1[j]++;
				b++;
				three = true;
			}

			if (two && three) break;
		}
	}
}

int calcCheckSum(int a, int b) {
	return a * b;
}

void getCommonLetters(char letters[], char words[][ARRAY_SIZE]) {
	for (int i = 0; i < LINES; i++) {
		for (int j = 0; j < LINES; j++) {
			int commonCount = 0;
			int uncommonIndex = 0;

			for (int k = 0; k < ARRAY_SIZE; k++) {
				if (words[i][k] == words[j][k]) {
					commonCount++;
				}
				else {
					uncommonIndex = k;
				}
			}

			if (commonCount == ARRAY_SIZE - 1) {
				int pos = 0;
				for (int k = 0; k < ARRAY_SIZE; k++) {
					if (k != uncommonIndex) {
						letters[pos++] = words[i][k];
					}
				}
			}
		}
	}
}

void printCommonLetters(char arr[]) {
	for (int i = 0; i < ARRAY_SIZE; i++) {
		cout << arr[i];
	}
}