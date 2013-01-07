#include <iostream>
#include "LongInt.h"

using namespace std;

LongInt::LongInt() {
	positive = true;
	length = 0;
}

LongInt::LongInt(const int &value) {
	positive = value >= 0;
	length = getIntLength(value);
	if(length) {
		int v = value;
		digits = new char[length];
		for(int i = 0; i < length; ++i, v /= 10) {
			digits[i] = v % 10;
		}
	}
}

LongInt::LongInt(const LongInt &value) {
	length = value.length;
	positive = value.positive;
	if(length) {
		digits = new char[length];
		memcpy(digits, value.digits, length * sizeof(char));
	}
}

LongInt::LongInt(const string &value) {
	const char *charArray = value.c_str();
	int stringLength = value.length();	

	if(charArray[stringLength] == '-') {
		positive = false;
	}

	length = 0;
	for(int i = 0; i < stringLength; ++i) {
		if(charArray[i] != 48 && charArray[i] != '-') {
			length = stringLength - i;
			break;
		}
	}

	if(length) {
		digits = new char[length];
		for(int i = 0; i < length; ++i) {
			digits[i] = charArray[stringLength - i - 1] - 48;
			if(digits[i] < 0 || digits[i] > 9)
				throw new exception("Bad number value.");
		}
	}
}

LongInt::~LongInt() {
	if(length) delete[] digits;
}

bool LongInt::operator=(const int &value) {
	if(length) delete[] digits;
	length = getIntLength(value);
	if(length) {
		digits = new char[length];

		int v = value;
		for(int i = 0; i < length; ++i, v /= 10) {
			digits[i] = v % 10;
		}
	}
	return true;
}

bool LongInt::operator=(const LongInt &value) {
	if(length) delete[] digits;
	length = value.length;
	if(length) {
		digits = new char[length];
		memcpy(digits, value.digits, length * sizeof(char));
	}
	return true;
}

int LongInt::operator[](const int &index) const {
	return (index < length ? digits[index] : 0);
}

LongInt& LongInt::operator+(const LongInt &value) const {
	LongInt *st = new LongInt();
	if(length == 0 && value.length == 0) return *st;

	st->length = max(length, value.length) + 1;
	st->digits = new char[st->length];
	st->digits[0] = 0;
	long sum;	
	
	for(int i = 0; i < st->length - 1; ++i) {
		sum = operator[](i) + value[i] + st->digits[i];
		st->digits[i + 1] = (char)(sum / 10);
		st->digits[i] = sum % 10;
	}
	if(st->digits[st->length - 1] == 0) st->length--;

	return *st;
}

LongInt& LongInt::operator-(const LongInt &value) const {
	const LongInt *p_value1 = 0;
	const LongInt *p_sub = 0;
	
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
				return *(new LongInt());
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

	LongInt *st = new LongInt();
	st->positive = !signInverse;
	st->length = max(length, value.length);
	st->digits = new char[st->length];

	const LongInt &value1 = *p_value1;
	const LongInt &sub = *p_sub;

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

LongInt& LongInt::operator*(const LongInt &value) const {
	LongInt *st = new LongInt();

	st->positive = (positive && true) == (value.positive && true);
	st->length = length + value.length;
	if(st->length == 0) return *(new LongInt());
	st->digits = new char[st->length];
	memset(st->digits, 0, st->length * sizeof(char));

	for(int i = 0; i < length; ++i)
		for(int j = 0; j < value.length; ++j) {
			st->digits[i + j] += digits[i] * value.digits[j];
			st->digits[i + j + 1] += st->digits[i + j] / 10;
			st->digits[i + j] %= 10;
		}

	if(st->digits[st->length - 1] == 0) st->length--;

	return *st;
}

LongInt& LongInt::DivShort(const int &value, int *mod) const {
	LongInt *st = new LongInt();
	//st->positive = positive == (value >= 0);// FUCKING FUCK
	st->positive = (positive && true) == (value >= 0);

	char *buf = new char[length];

	int rest = 0;
	int div = 0;
	int bufIndex = -1;
	int bufStartIndex = -1;
	for(int i = length - 1; i >= 0; --i) {
		rest = rest * 10 + digits[i];
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
		st->digits = new char[st->length];
		for(int i = 0; i < st->length; ++i) {
			st->digits[i] = buf[bufIndex - i];
		}
	}

	*mod = rest;

	delete[] buf;

	return *st;
}

LongInt& LongInt::Power(int power) const {
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

	LongInt mm = *this;
	LongInt *res = new LongInt(1);
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

void LongInt::Echo(ostream &st) const {
	if(length) {
		if(!positive) st << '-';
		for(int i = length - 1; i >= 0; --i) {
			st << (int)digits[i];
		}
		st << endl;
	} else {
		st << '0' << endl;
	}
}