#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <ctime>
#include <iomanip>
#include <string>
#include "Date.h"

using namespace std;

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