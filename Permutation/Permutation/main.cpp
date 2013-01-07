#include <iostream>
#include <fstream>

using namespace std;

void permutation(int level, int maxlevel, char* symbols, bool* use, char* current, ofstream *out) {
	if(level == maxlevel) {
		// Терминальное условие
		for(int i = 0; i < maxlevel; ++i) {
			*out << current[i];
		}
		*out << endl;
		return;
	}
	
	for(int i = 0; i < maxlevel; ++i) {
		if(!use[i]) {
			use[i] = true;
			current[level] = symbols[i];
			permutation(level + 1, maxlevel, symbols, use, current, out);
			use[i] = false;
		}
	}
}

int maintrol() {
	ifstream f_in("permut.in");
	ofstream* f_out = new ofstream("permut.out");

	bool use[16];
	memset(use, 0, sizeof(use));

	char symbols[16];
	int level = 0;
	char ch;
	for(level = 0; ; ++level) {
		f_in >> ch;
		if(f_in.eof()) break;
		symbols[level] = ch;
	}
	
	char *curr = new char[8];

	permutation(0, level, symbols, use, curr, f_out);

	f_in.close();
	f_out->close();

	return 0;
}