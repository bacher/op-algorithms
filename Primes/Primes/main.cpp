#include <fstream>

using namespace std;

int main() {
	ifstream f_in("primes2.in");
	ofstream f_out("primes2.out");

	long bound_low, bound_hi;
	f_in >> bound_low;
	f_in >> bound_hi;

	f_in.close();

	const int primes_max_count = 0x100000; // 1x4 MB;

	long *primes;
	primes = new long[primes_max_count];
	primes[0] = 2;

	long value;
	bool is_prime;
	int primes_index = 0;

	// [2012-10-04]
	// NOTE:
	// —трока кода: 38 //if(value*value > i) break;
	// »спользовал более простое усечение внутреннего цикла. ѕринцип сопоставим с предложенным вами на лекции, но
	// более простой и пон€тный.
	// ћой способ если по производительности то: умножение long*long, сравнение;
	//										¬аш: сравнение в условии цикла, умножение long*long, сравнение, инкремент.

	for(int i = 3; i <= bound_hi && primes_index + 1 < primes_max_count; i += 2) {
		is_prime = true;
		for(int j = 0; j <= primes_index; ++j) { // ѕротестировать и заменить на for(int j = 0;; ++j) {
			value = primes[j];
			if(value*value > i) break;
			if(i % value == 0) {
				is_prime = false;
				break;
			}
		}
		if(is_prime) {
			primes[++primes_index] = i;
		}
	}

	// Echo

	int start_index;
	bool is_res = false;
	for(start_index = 0; start_index <= primes_index; ++start_index) {
		if(primes[start_index] >= bound_low) break;
	}
	for(; start_index <= primes_index; ++start_index) {
		f_out << primes[start_index] << endl;
		is_res = true;
	}

	if(primes_index + 1 == primes_max_count) {
		f_out << "OVERFLOW";
	}

	if(!is_res) f_out << "Absent";

	f_out.close();

	delete[] primes;

	return 0;
}
