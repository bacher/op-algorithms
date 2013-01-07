#include <fstream>

using namespace std;

ofstream *f_out;
char *brackets;
int count;
char *stack;
int stackindex = -1;


void recurse(int level) {
	if(level == count) {
		for(int i = 0; i < count; ++i) {
			*f_out << brackets[i];
		}
		*f_out << endl;

		return;
	}

	if(count - level > stackindex + 1) {
		stackindex++;

		brackets[level] = '(';
		stack[stackindex] = '(';
		recurse(level + 1);

		brackets[level] = '[';
		stack[stackindex] = '[';
		recurse(level + 1);

		stackindex--;
	}

	if(stackindex >= 0) {
		if(stack[stackindex] == '(') {
			brackets[level] = ')';
			stackindex--;
			recurse(level + 1);
			stackindex++;
			stack[stackindex] = '(';
		} else {
			brackets[level] = ']';
			stackindex--;
			recurse(level + 1);
			stackindex++;
			stack[stackindex] = '[';
		}
	}
	
}


int main() {
	// Initialization
	ifstream f_in("bracket2.in");
	f_out = new ofstream("bracket2.out");

	f_in >> count;
	f_in.close();

	brackets = new char[count];
	stack = new char[count / 2];

	recurse(0);
	
	f_out->close();
}