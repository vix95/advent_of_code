#include <iostream>
#include <fstream>
using namespace std;

int main() {
	int freq = 0;
	int x;
	fstream f;

	f.open("input.txt");
	if (!f) {
		cout << "Unable to open file";
		cin.get();
		exit(1);
	}

	while (f >> x) {
		freq = freq + x;
	}

	f.close();
	cout << freq << endl;
	cin.get();
	return 0;
}