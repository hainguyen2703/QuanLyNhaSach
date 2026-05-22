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
	static int countHD;
	std::string maHD;
	Date date;
	std::string maKH;
	std::vector<Item> items;

	HoaDon(const std::string& maKH, const Date& date);	/* constructor có tham số */
	bool isVIP();				/* Kiểm tra xem khách hàng hạng vip không */

public:
	static HoaDon* taoHoaDon();
	void addItem(const Item& item);
	double getTongTien();
	void setMaHD(const std::string& maHD);
};

