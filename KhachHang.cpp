#include <iostream>
#include "KhachHang.h"
#include "Date.h"

using namespace std;

enum
{
	THUONG = 0,
	VIP = 1
};

/* Khởi tạo giá trị ban đầu cho biến Class */
int KhachHang::cntUserID = 0;

/* Khởi tạo giá trị ban đầu cho biến numOfUser */
static int numOfUser;


/* Hàm khởi tạo mặc định */
KhachHang::KhachHang(string& name, string& phone, string& mail, string& address, int& type)
{
	/* Set các thông tin đã collect từ trước */
	setName(name);
	setPhone(phone);
	setMail(mail);
	setAddress(address);
	setType(type);

	/* Lấy ngày hiện tại làm ngày đăng ký */
	this->ngayDK = getCurrentDate();

	/* Set ID */
	string baseID = "00000000";
	string nextID = to_string(KhachHang::cntUserID + 1);
	int replacePos = 8 - nextID.length();
	baseID.replace(replacePos, nextID.length(), nextID);
	this->id = "KH" + baseID;

	/* Tạo khách hàng thành công, tăng một customer */
	KhachHang::cntUserID++;
}

void KhachHang::XuatThongTin() const
{
	string loaiThe = (this->type == 1) ? "VIP" : "Thuong";

	cout << "Mã số khách hàng: " << this->id << endl
		<< "Tên khách hàng: " << this->name << endl
		<< "Số điện thoại: " << this->phone << endl
		<< "Email: " << this->mail << endl
		<< "Địa chỉ: " << this->address << endl
		<< "Ngày đăng ký: " << getDateString(this->ngayDK) << endl
		<< "Loại thẻ: " << loaiThe << endl;
}

void KhachHang::setName(string& name)
{
	this->name = name;
}
void KhachHang::setPhone(string& phone)
{
	this->phone = phone;
}
void KhachHang::setMail(string& mail)
{
	this->mail = mail;
}
void KhachHang::setAddress(string& addr)
{
	this->address = addr;
}
void KhachHang::setDate(Date& date)
{
	this->ngayDK = date;
}
void KhachHang::setType(int type)
{
	this->type = type;
}