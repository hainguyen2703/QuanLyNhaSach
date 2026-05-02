#pragma once
#include <string>
#include "Date.h"

using namespace std;

enum
{
	THUONG = 0,
	VIP = 1
};

class KhachHang
{
private:
	string id;
	string name;
	string phone;
	string mail;
	string address;
	Date ngayDK;	//Ngày đăng ký
	bool type;		//0: Thẻ thường, 1: Thẻ VIP
public:
	KhachHang();	//Hàm khởi tạo mặc định
	KhachHang(string id, string name, string phone, string mail, string address, Date ngayDK, bool type);	//Hàm khởi tạo có tham số
};

