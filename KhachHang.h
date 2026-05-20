#pragma once
#include <string>
#include "Date.h"

using namespace std;

enum
{
	THUONG = 0,
	VIP
};

class KhachHang
{
private:
	static int cntCustomerID;	//Biến của class để đếm số lượng Khách hàng
	string id;
	string name;
	string phone;
	string mail;
	string address;
	Date ngayDK;			//Ngày đăng ký
	int type;				//0: Thẻ thường, 1: Thẻ VIP

public:
	KhachHang(string &name, string &phone, string &mail, string &address, int &type);	//Hàm khởi tạo có tham số
	static KhachHang* createNewKhachHang();

	static void setCntCustomerID(const int& cnt);

	void setID(string& id);
	string getID();
	void setName(string& name);
	string getName();
	void setPhone(string& phone);
	string getPhone();
	void setMail(string& mail);
	string getMail();
	void setAddress(string& adr);
	string getAddress();
	void setRegisterDate(Date& date);
	Date getRegisterDate();
	void setType(int& type);
	int getType();
	string getLoaiThe() const;
	string getCsvString();
	void XuatThongTin() const;
};

