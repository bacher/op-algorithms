/*#include <fstream>

using namespace std;

ofstream *f_out;
int countofroundopen;
int countofsquareopen;
char *brackets;
int count;

void addclosure(int level) {
	int countofroundclosed = 0;
	int countofsquareclosed = 0;
	int j = level - 1;
	for(int i = level; i < count; ++i) {
		for(; j >= 0; --j) {
			if(brackets[j] == '(') {
				if(countofroundclosed == 0) {
					brackets[i] = ')';
					break;
				} else {
					countofroundclosed--;
				}
			} else if(brackets[j] == '[') {
				if(countofsquareclosed == 0) {
					brackets[i] = ']';
					break;
				} else {
					countofsquareclosed--;
				}
			} else if(brackets[j] == ')') {
				countofroundclosed++;
			} else if(brackets[j] == ']') {
				countofsquareclosed++;
			}
		}
	
	}
}

void recurse(int level) {
	if(countofroundopen + countofsquareopen == count / 2) {
		addclosure(level);
		return;
	}

	if(level == 0) {
		brackets[level] = '(';
		countofroundopen++;
		recurse(level + 1);

		brackets[level] = '[';
		countofsquareopen++;
		recurse(level + 1);
	} else {
		brackets[level] = '(';
		countofroundopen++;
		recurse(level + 1);

		brackets[level] = '[';
		countofsquareopen++;
		recurse(level + 1);

		if(brackets[level - 1] = '(') {
			brackets[level] = ')';
			countofroundopen--;
			recurse(level + 1);
		} else if(brackets[level - 1] = '[') {
			brackets[level] = ']';
			countofsquareopen--;
			recurse(level + 1);
		}
	}

}


int main_v1() {
	// Initialization
	ifstream f_in("bracket2.in");
	f_out = new ofstream("bracket2.out");

	f_in >> count;
	f_in.close();

	brackets = new char[count];

	countofroundopen = 0;
	countofsquareopen = 0;

	recurse(0);
	
	f_out->close();

	return 0;
}
*/