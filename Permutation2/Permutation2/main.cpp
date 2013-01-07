#include <iostream>
#include <fstream>

using namespace std;

ofstream *f_out;
int uniquescount;
int maxlevel;
int *uses;
char *symbols;
char *uniques;
char *current;


void permutation(int level) {
	if(level == maxlevel) {
		// Терминальное условие
		for(int i = 0; i < maxlevel; ++i) {
			*f_out << current[i];
		}
		*f_out << endl;
		return;
	}
	
	for(int i = 0; i < uniquescount; ++i) {
		if(uses[i] > 0) {
			uses[i]--;
			current[level] = uniques[i];
			permutation(level + 1);
			uses[i]++;
		}
	}
}

int main() {
	// Initialization
	ifstream f_in("permut2.in");
	f_out = new ofstream("permut2.out");

	symbols = new char[16];
	int count;
	char ch;
	for(count = 0; ; ++count) {
		f_in >> ch;
		if(f_in.eof()) break;
		symbols[count] = ch;
	}

	uniques = new char[count];
	uses = new int[count];
	int index = -1;
	for(int i = 0; i < count; ++i) {
		bool unique = true;
		for(int j = 0; j <= index; ++j) {
			if(uniques[j] == symbols[i]) {
				uses[j]++;
				unique = false;
				break;
			}
		}
		if(unique) {
			uniques[++index] = symbols[i];
			uses[index] = 1;
		}
	}
	
	current = new char[count];
	uniquescount = index + 1;
	maxlevel = count;
	permutation(0);

	f_in.close();
	f_out->close();
}