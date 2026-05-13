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
Date getDateFromString(const std::string& str);
std::istream& operator>>(std::istream& in, Date& date);
std::string getDateCsvString(const Date& date);