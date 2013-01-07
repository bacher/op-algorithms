#include <fstream>

using namespace std;


int s;
ofstream *f_out;
unsigned char *numbers;

void recurse(int level, int currentsum, int currentnumber) {
	if(s == currentsum) {
		if(s != currentnumber) {
			for(int i = 0; i < level - 1; ++i) {
				*f_out << (int)numbers[i] << '+';
			}
			*f_out << (int)numbers[level - 1] << endl;
		}
		return;
	}

	int st = s - currentsum;
	for(int i = currentnumber; i <= st; ++i) {
		numbers[level] = i;
		recurse(level + 1, currentsum + i, i);
	}
}

int main() {
	ifstream f_in("decomp.in");
	f_out = new ofstream("decomp.out");

	f_in >> s;
	f_in.close();

	numbers = new unsigned char[s];
	memset(numbers, 0, sizeof(unsigned char) * s);

	recurse(0, 0, 1);

	f_out->close();
}