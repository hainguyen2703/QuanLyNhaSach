#pragma once
#include <istream>
#include <string>

struct Date
{
	int day;
	int month;
	int year;
};

Date getCurrentDate();
std::string getDateString(const Date& date);
std::istream& operator>>(std::istream& in, Date& date);
std::string getDateCsvString(const Date& date);
