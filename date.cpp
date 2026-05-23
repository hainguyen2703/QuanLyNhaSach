#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <ctime>
#include <iomanip>
#include "Date.h"

using namespace std;

static bool isLeapYear(const int& year);

/* Hàm lấy và trả về thời gian hiện tại trong hệ thống */
Date getCurrentDate()
{
	Date date;

	/* Lấy thời gian hiện tại trong máy tính */
	time_t t = time(nullptr);
	tm* now = localtime(&t);

	/* Cập nhật ngày tháng năm */
	date.day = now->tm_mday;
	date.month = now->tm_mon + 1;
	date.year = now->tm_year + 1900;

	return date;
}

/* Hàm trả về ngày/tháng/năm theo dạng string */
string getDateString(const Date& date)
{
	/* Tạo string ngày và tháng */
	string day = (date.day > 9) ? to_string(date.day) : ("0" + to_string(date.day));
	string month = (date.month > 9) ? to_string(date.month) : ("0" + to_string(date.month));

	/* return string dd/mm/yyyy */
	return day + "/" + month + "/" + to_string(date.year);
}

/* Hàm chuyển string yyyy/mm/dd thành date */
Date getDateFromString(const string &str)
{
	string year = str.substr(0, 4);
	string month = str.substr(5, 2);
	string day = str.substr(8, 2);
	
	/* Set date*/
	Date date;
	date.day = stoi(day);
	date.month = stoi(month);
	date.year = stoi(year);

	return date;
}

/* Hàm trả về ngày/tháng/năm theo dạng string */
string getDateCsvString(const Date& date)
{
	/* Tạo string ngày và tháng */
	string day = (date.day > 9) ? to_string(date.day) : ("0" + to_string(date.day));
	string month = (date.month > 9) ? to_string(date.month) : ("0" + to_string(date.month));

	/* return string yyyy-mm-dd */
	return to_string(date.year) + "-" + month + "-" + day;
}

/* Nạp chồng hàm >> cho Date */
istream& operator>>(istream &in, Date& date)
{
	/* Biến dùng để tách ký tự / trong dd/mm/yyyy */
	char sep1, sep2;

	/* Lấy input từ istream */
	in >> date.day >> sep1 >> date.month >> sep2 >> date.year;

	/* Kiểm tra format dd/mm/yyyy hoặc dd-mm-yyyy*/
	bool formatCheck = ((sep1 == '/' && sep2 == '/') || (sep1 == '-' && sep2 == '-'));

	/* Check input */
	if (!in || !formatCheck)
	{
		/* Set fail bit */
		in.setstate(ios::failbit);
	}

	return in;
}

/* Hàm kiểm tra năm nhuần */
bool isLeapYear(const int& year)
{
	return (year % 400 == 0) || ((year % 4 == 0) && (year % 100 != 0));
}

/* Hàm lấy số ngày trong tháng */
int getDayInMonth(const Date& date)
{
	switch (date.month)
	{
		case 1: case 3: case 5: case 7: case 8: case 10: case 12: return 31;
		case 4: case 6: case 9: case 11: return 30;
		case 2: return (isLeapYear(date.year)) ? 29 : 28; 
	}
}

/* Hàm kiểm tra date có hợp lệ không */
bool validateDate(const Date& date)
{
	/* Kiểm tra năm */
	if ((date.year < 2000) ||
		(date.month < 1 || date.month > 12) ||
		(date.day < 1 || date.day > getDayInMonth(date)))
	{
		return false;
	}
		
	return true;
}
