#include <fstream>

using namespace std;

int main() {
	ifstream f_in("decomp.in");
	ofstream f_out("decomp.out");

	int s;
	f_in >> s;
	f_in.close();

	if(s != 2) {
		int last = s - 1;

		unsigned char *numbers = new unsigned char[s];
		memset(numbers, 0, sizeof(unsigned char) * s);

		int sum;
		bool endofcycle = false;
		int pos;
		int order = 1;
		int currentorder;
		bool shearorder = false;
		while(true) {
			if(shearorder) {
				shearorder = false;

				// Терминальное условие это ряд единиц [1+1+1+...+1]
				//if(numbers[pos] == 1) break;

				if(pos == 1) break;

				for(int i = pos - 1; i < s - 1; ++i) {
					numbers[i] = 1;
				}
				numbers[last] = 0;
				order++;
			}

			numbers[last]++;
			pos = last;
			currentorder = 1;
			while(true) {
				if(numbers[pos] == s) {
					/*if(pos == 0) {
						endofcycle = true;
						break;
					}*/

					currentorder++;	//можно вычислять через pos
					numbers[pos - 1]++;
					pos--;
				
				} else {
					break;
				}
			}		
			//if(endofcycle) break;

			if(currentorder >= order) {
				order = currentorder;
				int shear = s / order;
				if(s % order > 0) shear++;
				if(numbers[pos] == shear) {
					shearorder = true;
				}
			}

			for(int i = pos + 1; i < s; i++) {
				numbers[i] = numbers[pos];
			}

			sum = 0;
			for(int i = last; i >= 0 ; --i) {
				sum += numbers[i];
				if(sum > s) {
					break;
				}
			}
			if(sum == s) {
				for(int i = 0; i < last; ++i) {
					if(numbers[i] != 0) {
						f_out << (int)numbers[i] << '+';
					}
				}
				f_out << (int)numbers[last];
				f_out << endl;
			}
		}
	}

	for(int i = 0; i < s - 1; ++i) {
		f_out << '1' << '+';
	}
	f_out << '1';

	f_in.close();
	f_out.close();
}