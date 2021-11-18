#include "Time.h"

DateTime::DateTime(int year, int month, int day, int hour, int min) {
	this->year = year;
	this->month = month;
	this->day = day;
	this->hour = hour;
	this->min = min;
}

void DateTime::AddYears(int amount) {
	updateDate();
	this->year += 1;
}

void DateTime::AddMonths(int amount) {
	updateDate();
	this->month += 1;
}

void DateTime::AddHours(int amount) {
	updateDate();
	this->hour += 1;
}

void DateTime::AddDays(int amount) {
	updateDate();
	this->day += 1;
}

void DateTime::AddMinutes(int amount) {
	updateDate();
	this->min += 1;
}

std::string DateTime::ToString()
{
	return std::string();
}

void DateTime::updateDate()
{
	if (this->sec > 59) {
		AddMinutes(1);
		this->sec -= 59;
	}
	if (this->min > 59) {
		AddHours(1);
		this->min -= 59;
	}

	if (this->hour > 59) {
		AddDays(1);
		this->hour -= 59;
	}

	if (this->min > 59) {

		if (this->month == 2) {
			if (((this->year % 400 == 0) || (this->year % 4 == 0 && this->year % 100 != 0))) {
				if (this->day > 29) {
					AddMonths(1);
					this->day -= 29;
				}
			}
			else if (this->day > 28) {
				AddMonths(1);
				this->day -= 28;
			}
		}
		else if (this->month == 1 || this->month == 3 || this->month == 5 || this->month == 7 || this->month == 8 || this->month == 10 || this->month == 12) {
			if (this->day > 31) {
				AddMonths(1);
				this->day -= 31;
			}
		}
		else {
			if (this->day > 30) {
				AddMonths(1);
				this->day -= 30;
			}
		}
	}

	if (this->month > 12) {
		AddYears(1);
		this->month -= 12;
	}
}


