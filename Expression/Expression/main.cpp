#include <iostream>
#include <fstream>

using namespace std;

int *digits;
bool *signs;
int checksum;
int n;

bool expression(int level, int sum) {
	if(level == n) {
		return sum == checksum;
	}
	bool res1 = expression(level + 1, sum + digits[level]);	
	if(res1) {
		signs[level - 1] = true;
		return true;
	}
	bool res2 = expression(level + 1, sum - digits[level]);
	if(res2) {
		signs[level - 1] = false;
		return true;
	}
	return false;
}

int main() {
	ifstream f_in("expr.in");
	ofstream f_out("expr.out");

	f_in >> n;
	f_in >> checksum;

	signs = new bool[n - 1];
	digits = new int[n];
	for(int i = 0; i < n; ++i) {
		f_in >> digits[i];
	}

	int sum = digits[0];
	bool res = expression(1, sum);
	if(res) {
		for(int i = 0; i < n - 1; ++i) {
			f_out << digits[i] << (signs[i] ? '+' : '-');
		}
		f_out << digits[n - 1];
		f_out << '=' << checksum;
	} else {
		f_out << "No solution";
	}

	f_in.close();
	f_out.close();

	return 0;
}