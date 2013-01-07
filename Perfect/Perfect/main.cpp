#include <fstream>

using namespace std;

bool check_perfect(long value) {
	long dividers_sum = 1;

	long divider1;
	long divider2;

	for(int i = 2;; ++i) {
		divider1 = 0;
		divider2 = 1;
		if(value % i == 0) {
			divider1 = i;
			divider2 = value / i;
			if(divider1 >= divider2) break;
			dividers_sum += divider1 + divider2;
		}
	}

	if(divider1 == divider2) dividers_sum += divider1;

	return dividers_sum == value;
}

int main() {
	ifstream f_in("perfect.in");
	ofstream f_out("perfect.out");

	long a, b;
	f_in >> a >> b;
	f_in.close();

	long numbers[256];
	numbers[0] = 1;
	int numbersCount = 0;

	int step;
	long value;
	for(int i = 1; i < 256; ++i) {
		step = i*2 + 1;
		value = numbers[i-1] + step*step*step;
		if(value > b) {
			numbersCount = i;
			break;
		} else {
			numbers[i] = value;
		}
	}
	numbers[0] = 6;

	bool out_is_null = true;
	for(int i = 0; i < numbersCount; ++i) {
		value = numbers[i];
		if(check_perfect(value)) {
			if(value >= a) {
				f_out << value << endl;
				out_is_null = false;
			}
		}
	}

	if(out_is_null) f_out << "Absent";

	f_out.close();
	return 0;
}