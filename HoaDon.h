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
	long long tongBill;

	bool isVIP();				/* Kiểm tra xem khách hàng hạng vip không */

public:
	HoaDon(const std::string& maKH, const Date& date);	/* constructor có tham số */
	HoaDon(const std::string& maHD, const std::string& maKH, const Date& date, const std::vector<Item>& listItem, const long long& tongBill);	/* constructor có tham số */
	static void increaseMaHD();
	static void setCountMaHD(const int& cnt);
	void addItem(const Item& item);
	std::vector<Item> getListItems();
	void tinhTien();
	long long getTongTien();
	std::string getMaHD();
	bool setMaHD();
	Date getDate();
	void xuatHoaDon();
	std::string getCsvString() const;
};

