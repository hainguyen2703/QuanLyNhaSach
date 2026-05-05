#pragma once
#include <string>

struct Date
{
	int day;
	int month;
	int year;
};

extern Date getCurrentDate();
extern std::string getDateString(const Date& date);
