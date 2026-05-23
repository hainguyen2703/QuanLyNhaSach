#pragma once
#include <string>
#include <vector>
#include "Date.h"

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
	HoaDon(const std::string& maHD, const std::string& maKH, const Date& date, const std::vector<Item>& listItem);	/* constructor có tham số */
	static void increaseMaHD();
	static void setCountMaHD(const int& cnt);
	void addItem(const Item& item);
	std::vector<Item> getListItems();
	long long getTongTien();
	std::string getMaHD();
	bool setMaHD();
	Date getDate();
	void xuatHoaDon();
	std::string getCsvString() const;
};

