#pragma once
#include <string>
#include "Date.h"

using namespace std;

class KhachHang
{
private:
	static int cntUserID;	//Biến của class để đếm số lượng Khách hàng
	static int numOfUser;
	string id;
	string name;
	string phone;
	string mail;
	string address;
	Date ngayDK;			//Ngày đăng ký
	int type;				//0: Thẻ thường, 1: Thẻ VIP

public:
	KhachHang(string &name, string &phone, string &mail, string &address, int &type);	//Hàm khởi tạo có tham số
	string getID();
	string getName();
	string getPhone();
	string getMail();
	string getAddress();
	Date getRegisterDate();
	int getType();
	void XuatThongTin() const;
};

