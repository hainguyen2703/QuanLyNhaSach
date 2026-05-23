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

HoaDon::HoaDon(const string& maHD, const string& maKH, const Date& date, const vector<Item>& listItem)
{
	this->maHD = maHD;
	this->maKH = maKH;
	this->date = date;
	this->items = listItem;
}

void HoaDon::increaseMaHD()
{
	HoaDon::countMaHD++;
}

void HoaDon::setCountMaHD(const int& cnt)
{
	HoaDon::countMaHD = cnt;
}

/* Hàm add thêm item vào hóa đơn */
void HoaDon::addItem(const Item& newItem)
{
	/* Kiểm tra nếu isbn có trong items list rồi */
	for (Item& item : this->items)
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

/* Hàm lấy list item trong hóa đơn */
vector<Item> HoaDon::getListItems()
{
	return this->items;
}

/* Hàm tính tổng tiền hóa đơn */
long long HoaDon::getTongTien()
{
	long long bill = 0;
	for (const Item& item : this->items)
	{
		Book* book = BookManagement::getInstance().getBookByIsbn(item.isbn);
		/* Tính tiền trước giảm giá */
		long long sum = item.soLuong * book->getSellingPrice();

		/* Kiểm tra nếu có thể giảm 5% khi mua 5 quyển cùng loại */
		if (item.soLuong >= 5)
		{
			/* Giảm 5% */
			sum = sum * 95 / 100;
		}

		/* Add vào tổng bill */
		bill += sum;
	}

	/* Kiểm tra nếu có thể giảm 10% cho khách hàng VIP */
	if (this->isVIP() == true)
	{
		bill = bill * 90 / 100;
	}

	/* Add VAT 10% */
	bill += bill * 10 / 100;

	return bill;
}

/* Hàm kiểm tra khách hàng có phải hạng VIP không */
bool HoaDon::isVIP()
{
	return (CustomerManagement::getInstance().getKhByID(this->maKH)->getType() == 1);
}

/* Lấy mã hóa đơn */
string HoaDon::getMaHD()
{
	return this->maHD;
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

/* Lấy ngày lập hóa đơn */
Date HoaDon::getDate()
{
	return this->date;
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

/* Hàm lấy chuỗi string để lưu csv */
string HoaDon::getCsvString() const
{
	/* Format: maHD|maKH|Date|<isbn:soluong>|*/
	string csv = this->maHD + "|" + this->maKH + "|" + getDateCsvString(this->date) + "|";

	for (Item item : this->items)
	{
		csv += item.isbn + ":" + to_string(item.soLuong) + ";";
	}

	/* Xóa ký tự thừa cuối cùng */
	csv.pop_back();

	return csv;
}