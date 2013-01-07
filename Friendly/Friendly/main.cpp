#include <fstream>

using namespace std;

long sum_dirivers(long value) {
	long sum = 1;
	for(int i = 2; i*i < value; ++i) {
		if(value % i == 0) {
			sum += i + value/i;
		}
	}
	return sum;
}

int main() {
	ifstream f_in("friendly.in");
	ofstream f_out("friendly.out");

	long bound_low, bound_hi;
	f_in >> bound_low >> bound_hi;
	f_in.close();

	long dirivers[2048];
	int dirivers_index = -1;
	long sum1;
	bool is_result = false;

	for(int i = bound_low; i < bound_hi; ++i) {
		sum1 = sum_dirivers(i);
		if(i >= sum1) continue;

		if(sum1 >= bound_low && sum1 <= bound_hi) {
			if(i == sum_dirivers(sum1)) {
				f_out << i << " " << sum1 << endl;
				is_result = true;
			}
		}
	}

	if(!is_result) f_out << "Absent";

	return 0;
}