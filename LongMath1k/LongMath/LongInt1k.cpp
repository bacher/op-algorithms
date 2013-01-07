#include <iostream>
#include "LongInt1k.h"

using namespace std;

LongInt1k::LongInt1k() {
	positive = true;
	length = 0;
}

LongInt1k::LongInt1k(const int &value) {
	positive = value >= 0;
	//length = getIntLength(value);	
	int v = value;
	length = 3;
	digits = new int[length];
	for(int i = 0; i < length; ++i, v /= 10000) {
		digits[i] = v % 10000;		
	}
	if(digits[2] == 0) {
		length = 2;
		if(digits[1] == 0) {
			length = 1;
			if(digits[0] == 0) {
				length = 0;
				delete digits;
			}
		}
	}
}

LongInt1k::LongInt1k(const LongInt1k &value) {
	length = value.length;
	positive = value.positive;
	if(length) {
		digits = new int[length];
		memcpy(digits, value.digits, length * sizeof(int));
	}
}

LongInt1k::LongInt1k(const string &value) {
	int offset = value.length() % 4;
	string v;
	if(offset == 0) v = "";
	else if(offset == 1) v = "000";
	else if(offset == 2) v = "00";
	else if(offset == 3) v = "0";
	v.append(value);

	length = v.length() / 4;
	digits = new int[length];
	const char *chars = v.c_str();

	int i1, i2, i3, i4;
	for(int i = 0; i < length; ++i) {
		 i1 = chars[(length * 4 - 1) - i * 4] - 48;
		 i2 = chars[(length * 4 - 1) - i * 4 - 1] - 48;
		 i3 = chars[(length * 4 - 1) - i * 4 - 2] - 48;
		 i4 = chars[(length * 4 - 1) - i * 4 - 3] - 48;
		 digits[i] = i1 + i2*10 + i3*100 + i4*1000;
	}
}

LongInt1k::~LongInt1k() {
	if(length) delete[] digits;
}

bool LongInt1k::operator=(const int &value) {
	if(length) delete[] digits;
	length = getIntLength(value);
	if(length) {
		digits = new int[length];

		int v = value;
		for(int i = 0; i < length; ++i, v /= 10) {
			digits[i] = v % 10;
		}
	}

	return true;
}

bool LongInt1k::operator=(const LongInt1k &value) {
	if(length) delete[] digits;
	length = value.length;
	if(length) {
		digits = new int[length];
		memcpy(digits, value.digits, length * sizeof(int));
	}
	return true;
}

int LongInt1k::operator[](const int &index) const {
	return (index < length ? digits[index] : 0);
}

LongInt1k& LongInt1k::operator+(const LongInt1k &value) const {
	LongInt1k *st = new LongInt1k();
	if(length == 0 && value.length == 0) return *st;

	st->length = max(length, value.length) + 1;
	st->digits = new int[st->length];
	st->digits[0] = 0;
	int sum;
	
	for(int i = 0; i < st->length - 1; ++i) {
		sum = operator[](i) + value[i] + st->digits[i];
		st->digits[i + 1] = sum / 10000;
		st->digits[i] = sum % 10000;
	}
	if(st->digits[st->length - 1] == 0) st->length--;

	return *st;
}

LongInt1k& LongInt1k::operator-(const LongInt1k &value) const {
	const LongInt1k *p_value1 = 0;
	const LongInt1k *p_sub = 0;
	
	bool signInverse = false;

	if(length > value.length) {
		p_value1 = this;
		p_sub = &value;
	} else if(length < value.length) {
		p_value1 = &value;
		p_sub = this;
	} else {
		for(int i = length - 1;; --i) {
			if(i == -1) {
				return *(new LongInt1k());
			}
			if(operator[](i) > value[i]) {
				p_value1 = this;
				p_sub = &value;
				break;
			} else if(operator[](i) < value[i]) {
				p_value1 = &value;
				p_sub = this;
				signInverse = true;
				break;
			}
		}		
	}

	LongInt1k *st = new LongInt1k();
	st->positive = !signInverse;
	st->length = max(length, value.length);
	st->digits = new int[st->length];

	const LongInt1k &value1 = *p_value1;
	const LongInt1k &sub = *p_sub;

	int difference;
	for(int i = 0; i < st->length; ++i) {
		difference = value1[i] - sub[i];
		if(difference < 0) {
			st->digits[i + 1] = -1;
			st->digits[i] += difference + 10;
		} else {
			st->digits[i] = difference;
		}
	}

	int realLength = 0;
	for(int i = st->length - 1; i >= 0; --i) {
		if(st->digits[i] > 0) {
			realLength = i + 1;
			break;
		}
	}
	st->length = realLength;

	if(st->length == 0) delete[] digits;

	return *st;
}

LongInt1k& LongInt1k::operator*(const LongInt1k &value) const {
	LongInt1k *st = new LongInt1k();

	st->positive = (positive && true) == (value.positive && true);
	st->length = length + value.length;
	if(st->length == 0) return *(new LongInt1k());
	st->digits = new int[st->length];
	memset(st->digits, 0, st->length * sizeof(int));

	for(int i = 0; i < length; ++i)
		for(int j = 0; j < value.length; ++j) {
			st->digits[i + j] += digits[i] * value.digits[j];
			st->digits[i + j + 1] += st->digits[i + j] / 10000;
			st->digits[i + j] %= 10000;
		}

	if(st->digits[st->length - 1] == 0) st->length--;

	return *st;
}

LongInt1k& LongInt1k::DivShort(const int &value, int *mod) const {
	LongInt1k *st = new LongInt1k();
	//st->positive = positive == (value >= 0);// FUCKING FUCK
	st->positive = (positive && true) == (value >= 0);

	int *buf = new int[length];

	int rest = 0;
	int div = 0;
	int bufIndex = -1;
	int bufStartIndex = -1;
	for(int i = length - 1; i >= 0; --i) {
		rest = rest * 10000 + digits[i];
		div = rest / value;
		if(div > 0) {
			buf[++bufIndex] = div;
			if(bufStartIndex == -1) {
				bufStartIndex = bufIndex;
			}
			rest %= value;
		} else {
			buf[++bufIndex] = 0;
		}
	}
	if(bufStartIndex == -1) {
		st->length = 0;
	} else {
		st->length = bufIndex - bufStartIndex + 1;
		st->digits = new int[st->length];
		for(int i = 0; i < st->length; ++i) {
			st->digits[i] = buf[bufIndex - i];
		}
	}

	*mod = rest;

	delete[] buf;

	return *st;
}

LongInt1k& LongInt1k::Power(int power) {
	int pow = power;
	int p = 2;
	int grade;
	for(grade = 1; p <= pow; ++grade, p *= 2) { }
	grade--;
	p >>= 1;

	bool *frame = new bool[grade];
	memset(frame, 0, grade * sizeof(bool));

	for(int i = grade; i > 0; --i, p >>= 1) {
		if(pow - p >= 0) {
			pow -= p;
			frame[i] = true;
		}
	}
	if(pow == 1) frame[0] = true;

	LongInt1k mm = *this;
	LongInt1k *res = new LongInt1k(1);
	for(int i = 0; i <= grade; ++i, mm = mm * mm) {		
		if(frame[i]) {
			*res = *res * mm;
		}
	}

	if(power % 2 == 0) {
		res->positive = true;
	} else {
		res->positive = positive;
	}

	return *res;
}

void LongInt1k::Echo(ostream &st) const {
	if(length) {
		if(!positive) st << '-';
		for(int i = length - 1; i >= 0; --i) {
			if(i != length - 1) {
				if(digits[i] / 10 == 0) st << "000";
				else if(digits[i] / 100 == 0) st << "00";
				else if(digits[i] / 1000 == 0) st << "0";
			}
			st << digits[i];
		}
		st << endl;
	} else {
		st << '0' << endl;
	}
}