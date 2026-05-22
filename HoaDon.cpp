#include <iostream>
#include "HoaDon.h"
#include "CustomerManagement.h"
#include "BookManagement.h"
#include "common.h"
#include "customer_ultis.h"

using namespace std;

/* Khởi tạo mặc định = 0 */
int HoaDon::countHD = 0;

/* Constructor */
HoaDon::HoaDon(const string& maKH, const Date& date)
{
	this->maKH = maKH;
	this->date = date;
}

/* Hàm lấy thông tin và tạo hóa đơn */
HoaDon* HoaDon::taoHoaDon()
{
	/* Lấy mã khách hàng */
	cout << "Nhập vào mã khách hàng: ";
	string maKH;
	getStringLine(maKH);
	if (ktUserID(maKH) != true)
	{
		cout << "Mã khách hàng không hợp lệ" << endl;
		return NULL;
	}

	/* Lấy ngày lập hóa đơn */
	Date date;
	cout << "Ngày xuất hóa đơn: " << endl;
	cin >> date;

	/* Kiểm tra input */
	if (!cin)
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Ngày không hợp lệ" << endl;
		return NULL;
	}
	else
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

	/* Kiểm tra ngày */
	if (validateDate(date) != true)
	{
		cout << "Ngày không hợp lệ" << endl;
		return NULL;
	}

	/* Tạo và trả về hóa đơn chưa có item */
	return new HoaDon(maKH, date);
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
void HoaDon::setMaHD(const string& maHD)
{
	this->maHD = maHD;
}