#include <fstream>

using namespace std;

bool isBadYear(int year) {
	return year % 400 == 0 || (year % 4 == 0 && year % 100 != 0);
}

void main() {
	ifstream f_in("birthday.in");
	ofstream f_out("birthday.out");

	int bday, bmonth;
	int day, month, year;
	int daysinmonths[12];
	daysinmonths[0] = 31;
	daysinmonths[1] = 28; // Февраль
	daysinmonths[2] = 31;
	daysinmonths[3] = 30;
	daysinmonths[4] = 31;
	daysinmonths[5] = 30;
	daysinmonths[6] = 31;
	daysinmonths[7] = 31;
	daysinmonths[8] = 30;
	daysinmonths[9] = 31;
	daysinmonths[10] = 30;
	daysinmonths[11] = 31;

	f_in >> bday >> bmonth;
	f_in >> day >> month >> year;

	f_in.close();

	bday--;
	bmonth--;
	day--;
	month--;

	//---

	int days = -day;

	while(true) {
		if(month == bmonth) {
			if(bmonth == 1 && bday == 28) {
				if(isBadYear(year)) {					
					if(days + bday >= 0) {
						days += bday;
						break;
					}
				}
			} else {				
				if(days + bday >= 0) {
					days += bday;
					break;
				}
			}			
		}
		days += daysinmonths[month];
		if(month == 1) {
			if(isBadYear(year)) days++;
		}

		month++;
		if(month == 12) {
			year++;
			month = 0;
		}
	}
	f_out << days;

	//---
	f_out.close();
}
