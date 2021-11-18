#pragma once
#include <iostream>
class DateTime
{
public:
	int year;
	int month;
	int day;
	int hour;
	int min;
	int sec;

	DateTime(int year, int month, int day, int hour, int min);

	void AddYears(int amount);

	void AddMonths(int amount);

	void AddDays(int amount);

	void AddHours(int amount);

	void AddMinutes(int amount);

	std::string ToString();

private:
	void updateDate();
};

