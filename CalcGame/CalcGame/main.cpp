#include <fstream>

using namespace std;

bool check_value(long value) {
	long number = value % 10;
	int order = 10;
	while(true) {
		if(value/order == 0) return true;
		if((value % (order*10)) / order != number) return false;		
		order *= 10;
	}
}

int main() {
	ifstream f_in("calcgame.in");
	ofstream f_out("calcgame.out");

	long k;
	f_in >> k;
	f_in.close();
	
	long kt = k % 100;
	bool is_ok = false;
	long number;
	long step;

	long mod;
	for(int i = 1;; ++i) {
		mod = (kt*i) % 100;
		if(i != 1 && mod == kt) break;
		if(mod % 10 == mod / 10) {
			if(check_value(i*k)) {
				step = i;
				number = mod % 10;
				is_ok = true;
				break;
			}
		}		
	}

	if(is_ok) {
		f_out << k << " " << number << " " << step << endl;
	} else {
		//f_out << "Impossible";
	}

	f_out.close();

	return 0;
}