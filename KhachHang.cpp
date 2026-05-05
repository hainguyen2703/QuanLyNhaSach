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
KhachHang::KhachHang()
{
	cout << "Nhập vào tên khách hàng: ";
	getline(cin, this->name);
	cout << "Nhập vào số điện thoại: ";
	getline(cin, this->phone);
	cout << "Nhập vào mail khách hàng: ";
	getline(cin, this->mail);
	cout << "Nhập vào địa chỉ: ";
	getline(cin, this->address);
	cout << "Hạng khách hàng (0: Thường, 1: VIP): ";
	cin >> this->type;

	/* Xóa ký tự \n */
	(void)getchar();

	/* Lấy ngày hiện tại làm ngày đăng ký */
	this->ngayDK = getCurrentDate();

	/* Set ID */
	string baseID = "00000000";
	string nextID = to_string(KhachHang::cntUserID + 1);
	int replacePos = 8 - nextID.length();
	baseID.replace(replacePos, nextID.length(), nextID);
	this->id = "KH" + baseID;
	KhachHang::cntUserID++;
}

void KhachHang::XuatThongTin() const
{
	cout << "Mã số khách hàng: " << this->id << endl
		<< "Tên khách hàng: " << this->name << endl
		<< "Số điện thoại: " << this->phone << endl
		<< "Email: " << this->mail << endl
		<< "Địa chỉ: " << this->address << endl
		<< "Ngày đăng ký: " << getDateString(this->ngayDK) << endl;
}
