#ifndef LONGINT_H
#define LONGINT_H

#include <iostream>

using namespace std;

class LongInt {
public:
	LongInt();
	LongInt(const int &value);
	LongInt(const LongInt &value);
	LongInt(const string &value);
	virtual ~LongInt();

	bool operator=(const int &value);
	bool operator=(const LongInt &value);
	LongInt& operator+(const LongInt &value) const;
	LongInt& operator-(const LongInt &value) const;
	LongInt& operator*(const LongInt &value) const;
	LongInt& DivShort(const int &value, int *mod) const;
	int operator[](const int &index) const;
	void Echo(ostream &st) const;
	LongInt& Power(int power) const;
protected:
	bool positive;
	long length;
	char *digits;

	inline int max(int value1, int value2) const {
		return (value1 > value2 ? value1 : value2);
	}
	inline int min(int value1, int value2) const {
		return (value1 > value2 ? value2 : value1);
	}
	static int getIntLength(const int &value) {
		int _capability = 0;
		int long_value = 1000000000;
		for(int i = 10; i > 0; --i, long_value /= 10) {
			if(value / long_value > 0) {
				_capability = i;
				break;
			}
		}
		return _capability;
	}
};

#endif