#pragma once
#include <string>
#include <vector>
#include "Date.h"

#define VAT 0.1

/* Struct mapping isbn và soluong */
struct Item {
	std::string isbn;
	int soLuong;
};

class HoaDon
{
private:
	static int countMaHD;
	std::string maHD;
	Date date;
	std::string maKH;
	std::vector<Item> items;

	bool isVIP();				/* Kiểm tra xem khách hàng hạng vip không */

public:
	HoaDon(const std::string& maKH, const Date& date);	/* constructor có tham số */
	static void increaseMaHD();
	void addItem(const Item& item);
	double getTongTien();
	bool setMaHD();
	void xuatHoaDon();
};

