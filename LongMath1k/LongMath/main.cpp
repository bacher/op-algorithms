#include <string>
#include <iostream>
#include <fstream>

#include "LongInt1k.h"

using namespace std;

int main() {
	ifstream f_in("divshort.in");
	ofstream f_out("divshort.out");

	string n1;
	int div;
	getline(f_in, n1);
	f_in >> div;
	f_in.close();

	LongInt1k i1(n1);

	int mod;
	LongInt1k i2 = i1.DivShort(div, &mod);

	i2.Echo(f_out);
	f_out << mod;
	f_out.close();

	return 0;
}
