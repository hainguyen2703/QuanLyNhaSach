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
	static int cntCustomerID;	//Biến của class để đếm số lượng ID Khách hàng nhằm tự tạo ID mới
	string id;
	string name;
	string phone;
	string mail;
	string address;
	Date ngayDK;				//Ngày đăng ký
	int type;					//0: Thẻ thường, 1: Thẻ VIP

public:
	KhachHang(string &name, string &phone, string &mail, string &address, int &type);	//Hàm khởi tạo có tham số
	static KhachHang* createNewKhachHang();												//Hàm tạo khách hàng mới

	static void setCntCustomerID(const int& cnt);

	/* Các setter và getter functions */
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

	/* Hàm tạo chuỗi string để lưu xuống csv */
	string getCsvString();
	/* Hàm xuất thông tin của khách hàng theo format */
	void XuatThongTin() const;
};

