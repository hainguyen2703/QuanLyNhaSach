#include <iostream>
#include <iomanip>
#include "HoaDon.h"
#include "CustomerManagement.h"
#include "BookManagement.h"
#include "common.h"

using namespace std;

int HoaDon::countMaHD = 0;

/* Constructor */
HoaDon::HoaDon(const string& maKH, const Date& date)
{
	this->maKH = maKH;
	this->date = date;
}

void HoaDon::increaseMaHD()
{
	HoaDon::countMaHD++;
}

/* Hàm add thêm item vào hóa đơn */
void HoaDon::addItem(const Item& newItem)
{
	/* Kiểm tra nếu isbn có trong items list rồi */
	for (Item item : this->items)
	{
		if (newItem.isbn == item.isbn)
		{
			item.soLuong += newItem.soLuong;
			return;
		}
	}

	/* item chưa có -> push back */
	this->items.push_back(newItem);
}

/* Hàm tính tổng tiền hóa đơn */
double HoaDon::getTongTien()
{
	double bill = 0;
	for (Item item : this->items)
	{
		Book* book = BookManagement::getInstance().getBookByIsbn(item.isbn);
		bill += item.soLuong * book->getSellingPrice();
	}

	return bill;
}

/* Hàm kiểm tra khách hàng có phải hạng VIP không */
bool HoaDon::isVIP()
{
	return CustomerManagement::getInstance().getKhByID(this->maKH)->getType();
}

/* Hàm set mã hóa đơn */
bool HoaDon::setMaHD()
{
	if (this->items.empty())
		return false;

	string newMaHD = "00000000";
	string nextID = to_string(HoaDon::countMaHD + 1);
	size_t replacePos = 8 - nextID.length();
	newMaHD.replace(replacePos, nextID.length(), nextID);
	this->maHD = "HD" + newMaHD;

	return true;
}

/* Hàm in thông tin hóa đơn */
void HoaDon::xuatHoaDon()
{
	cout << setfill('=')
		<< setw(42) << "" << endl;
	print_utf8_left("Hóa đơn", 10);
	cout << this->maHD << endl;
	cout << setfill('=') << setw(42) << "" << endl;
	print_utf8_left("Mã khách hàng", 20);
	cout << ":" << this->maKH << endl
		<< "Mã isbn - số lượng:" << endl;

	for (Item item : this->items)
	{
		cout << setfill(' ') << setw(15) << item.isbn
			<< " - " << item.soLuong << " cuốn" << endl;
	}

	cout << setfill('_') << setw(42) << "" << endl;
	print_utf8_left("Tổng tiền", 10);
	cout << ": " << this->getTongTien() << " vnd" << endl;
	cout << setfill('=') << setw(42) << "" << endl;
}