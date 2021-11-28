#include "Time.h"

DateTime::DateTime(int year, int month, int day, int hour, int min) {
	this->year = year;
	this->month = month;
	this->day = day;
	this->hour = hour;
	this->min = min;
}

void DateTime::AddYears(int amount) {
	this->year += 1;
}

void DateTime::AddMonths(int amount) {
	this->month += 1;
	updateMonths();
}

void DateTime::AddHours(int amount) {
	this->hour += 1;
	updateHours();
}

void DateTime::AddDays(int amount) {
	this->day += 1;
	updateDays();
}

void DateTime::AddMinutes(int amount) {
	this->min += 1;
	updateMinutes();
}

std::string DateTime::TimeToString()
{
	std::string timeStr;
	if (hour < 10) {
		timeStr = "0" + std::to_string(hour);
	}
	else {
		timeStr = std::to_string(hour);
	}
	timeStr += ":";
	if (min < 10) {
		timeStr += "0" + std::to_string(min);
	}
	else {
		timeStr += std::to_string(min);
	}

	return timeStr;
}

std::string DateTime::DateToString()
{
	std::string dateStr;
	if (day < 10) {
		dateStr = "0" + std::to_string(day);
	}
	else {
		dateStr = std::to_string(day);
	}
	dateStr += "/";
	if (month < 10) {
		dateStr += "0" + std::to_string(month);
	}
	else {
		dateStr += std::to_string(month);
	}
	dateStr += "/";
	dateStr += std::to_string(year);

	return dateStr;
}

void DateTime::updateMinutes(){
	if (this->min > 59) {
		AddHours(1);
		this->min -= 60;
	}
}

void DateTime::updateHours(){
	if (this->hour > 59) {
		AddDays(1);
		this->hour -= 60;
	}
}

void DateTime::updateDays(){
	if (this->day > 29) {

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
}

void DateTime::updateMonths(){
	if (this->month > 12) {
		AddYears(1);
		this->month -= 12;
	}
}


