#include <fstream>

using namespace std;

int main() {
	ifstream f_in("pfactor.in");
	ofstream f_out("pfactor.out");

	long value, tmp;

	f_in >> value;
	f_in.close();

	tmp = value;

	const int factors_max_count = 2048;
	long factors[factors_max_count];
	int factors_index = -1;
	
	for(int i = 2; i*i <= tmp; ++i) {
		while(true) {
			if(tmp % i == 0) {
				factors[++factors_index] = i;
				tmp /= i;
			} else {
				break;
			}
		}
	}

	if(tmp != 1) factors[++factors_index] = tmp;

	for(int i = 0; i < factors_index; ++i) {
		f_out << factors[i] << '*';
	}
	f_out << factors[factors_index];
	f_out.close();

	return 0;
}