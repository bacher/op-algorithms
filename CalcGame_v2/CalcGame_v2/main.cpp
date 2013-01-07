#include <fstream>

using namespace std;

int main() {
	ifstream f_in("calcgame.in");
	ofstream f_out("calcgame.out");

	const int max_number_count = 4096;

	long value;
	f_in >> value;
	f_in.close();

	long rest = 1;
	long new_slg = 1;
	bool flag = false;

	for(int i = 1;; ++i) {
		for(int j = 1; j < 10; ++j) {
			if((rest * j) % value == 0) {
				f_out << j << " " << i;
				flag = true;
				break;
			}
		}

		if(flag) break;

		if(i == max_number_count) {
			f_out << "Impossible";
			break;
		}

		new_slg = ((10 % value) * new_slg) % value;
		rest = (new_slg + rest) % value;
	}

	f_out.close();

	return 0;
}