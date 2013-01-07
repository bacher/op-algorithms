#include <iostream>
#include <fstream>

using namespace std;

char *symbols;
bool *use;
char *current;
ofstream *f_out;
int maxlevel;

void permutation(int level) {
	if(level == maxlevel) {
		// Терминальное условие
		for(int i = 0; i < maxlevel; ++i) {
			*f_out << current[i];
		}
		*f_out << endl;
		return;
	}
	
	for(int i = 0; i < maxlevel; ++i) {
		if(!use[i]) {
			use[i] = true;
			current[level] = symbols[i];
			permutation(level + 1);
			use[i] = false;
		}
	}
}

int main() {
	// Initialization
	ifstream f_in("permut.in");
	f_out = new ofstream("permut.out");

	use = new bool[16];
	memset(use, 0, sizeof(bool) * 16);

	symbols = new char[16];
	current = new char[16];
	int level;
	char ch;
	//----

	for(level = 0; ; ++level) {
		f_in >> ch;
		if(f_in.eof()) break;
		symbols[level] = ch;
	}
	maxlevel = level;
	
	permutation(0);

	f_in.close();
	f_out->close();
}