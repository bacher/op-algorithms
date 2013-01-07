#include <fstream>

using namespace std;

int main() {
	ifstream f_in("sumfraction.in");
	ofstream f_out("sumfraction.out");

	long count;
	f_in >> count;

	long divident = 0, divider = 1;
	long t_divident, t_divider;

	for(int i = 0; i < count; ++i) {
		f_in >> t_divident >> t_divider;

		if(divider % t_divider == 0) {
			divident += t_divident * (divider / t_divider);
		} else if(t_divider % divider == 0) {
			divident = divident * (t_divider / divider) + t_divident;
			divider = t_divider;
		} else {
			divident = divident * t_divider + t_divident * divider;
			divider *= t_divider;
		}
	}

	for(int i = 2; i <= divider && i <= divident; ++i) {
		while(divident % i == 0 && divider % i == 0) {
			divident /= i;
			divider /= i;
		}
	}

	f_out << divident << " " << divider;

	return 0;
}