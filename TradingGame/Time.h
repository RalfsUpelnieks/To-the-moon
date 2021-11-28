#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <iomanip>
#include <sstream>
class DateTime
{
public:
	int year;
	int month;
	int day;
	int hour;
	int min;

	DateTime(int year, int month, int day, int hour, int min);

	void AddYears(int amount);

	void AddMonths(int amount);

	void AddDays(int amount);

	void AddHours(int amount);

	void AddMinutes(int amount);

	std::string TimeToString();

	std::string DateToString();

private:
	void updateMinutes();
	void updateHours();
	void updateDays();
	void updateMonths();
};

