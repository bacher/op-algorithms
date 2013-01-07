#include <string>
#include <istream>
#include <iostream>
#include <fstream>

using namespace std;

int main() {
	const int maxLength = 30000;

	ifstream f_in("longsum.in");
	ofstream f_out("longsum.out");
	

	char *n1 = new char[maxLength];
	char *n2 = new char[maxLength];

	string str;

	f_in >> str;
	int n1Lenght = str.length();
	const char *strArray = str.c_str();
	for(int i = 0; i < n1Lenght; ++i) {
		n1[i] = strArray[i] - 48;
	}

	f_in >> str;
	int n2Lenght = str.length();
	strArray = str.c_str();
	for(int i = 0; i < n2Lenght; ++i) {
		n2[i] = strArray[i] - 48;
	}

	int a = 0;

	delete[] n1;
	delete[] n2;
}