#ifndef LONGINT_H
#define LONGINT_H

#include <iostream>

using namespace std;

class LongInt1k {
public:
	LongInt1k();
	LongInt1k(const int &value);
	LongInt1k(const LongInt1k &value);
	LongInt1k(const string &value);
	virtual ~LongInt1k();
	bool operator=(const int &value);
	bool operator=(const LongInt1k &value);
	LongInt1k& operator+(const LongInt1k &value) const;
	LongInt1k& operator-(const LongInt1k &value) const;
	LongInt1k& operator*(const LongInt1k &value) const;
	LongInt1k& DivShort(const int &value, int *mod) const;
	int operator[](const int &index) const;
	void Echo(ostream &st) const;
	LongInt1k& Power(int power);
protected:
	bool positive;
	long length;
	int *digits;

	inline int max(int value1, int value2) const {
		return (value1 > value2 ? value1 : value2);
	}
	inline int min(int value1, int value2) const {
		return (value1 > value2 ? value2 : value1);
	}
	static int getIntLength(const int &value) {
		int _capability = 0;
		int long_value = 1000000000;
		for(int i = 4; i > 0; --i) {
			if(value / long_value > 0) {
				_capability = i;
				break;
			}
			if(i == 4) {
				long_value /= 10;
			} else {
				long_value /= 10000;
			}
		}
		return _capability;
	}
};

#endif