#include <string>
#include <iostream>
#include <fstream>

#include "LongInt.h"

using namespace std;

int main() {
	ifstream f_in("power.in");
	ofstream f_out("power.out");

	int d;
	int pow;

	f_in >> d;
	f_in >> pow;
	f_in.close();

	LongInt i1 = d;
	LongInt i2 = i1.Power(pow);

	i2.Echo(f_out);
	f_out.close();

	return 0;
}
