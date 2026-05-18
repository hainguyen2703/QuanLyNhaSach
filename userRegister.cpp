#include <iostream>
#include <string>
#include <cctype>
#include <iomanip>
#include "common.h"
#include "UserManagement.h"
#include "userRegister.h"

using namespace std;

/* Static function prototype */
static KhachHang* collectUserInfo();
static bool phoneValidate(const string& phone);
static bool mailValidate(const string& mail);

/* Hàm yêu cầu user đưa input để tạo tài khoảng */
KhachHang* collectUserInfo()
{
	/* 1. Họ tên */
	string hoten;	/* Biến chứa tên khách hàng */
	cout << setw(30) << setfill('*') << "*" << endl;
	cout << "Tạo tài khoảng" << endl;
	cout << setw(30) << setfill('*') << "" << endl;
	cout << "Họ tên khách hàng: ";
	getline(cin, hoten);
	/* Kiểm tra nếu chuỗi input toàn khoảng trắng */
	if (isAllBlank(hoten)) return nullptr;

	/* 2. Số điện thoại */
	string phone;
	cout << "Số điện thoại: ";
	getline(cin, phone);
	/* Kiểm tra phone input */
	if (phoneValidate(phone) == false)
		return nullptr;

	/* 3. Mail */
	string mail;
	cout << "Mail: ";
	getline(cin, mail);
	/* Kiểm tra mail input */
	if (mailValidate(mail) != true) 
		return nullptr;
	else
		mail = toLower(mail);

	/* 4. Địa chỉ */
	string address;
	cout << "Địa chỉ: ";
	getline(cin, address);
	/* Kiểm tra địa chỉ */
	if (address.empty())
	{
		cout << "Địa chỉ không hợp lệ!!\n";
		return nullptr;
	}

	/* 5. Loại thẻ */
	int the;
	cout << "Loại thẻ: ";
	cin >> the;
	cin.ignore(100, '\n');
	if (the != 0 && the != 1)
	{
		cout << "Không hợp lệ!!" << endl;
		cout << "Mặc định hạng thẻ thường!!!" << endl;
		the = 0;
	}

	/* Tạo user mới */
	KhachHang* newCustomer = new KhachHang(hoten, phone, mail, address, the);

	return newCustomer;
}

/* Hàm thu thập thông tin và tạo khách hàng mới */
void createUser()
{
	/* Thu thập thông tin */
	KhachHang* newUser = collectUserInfo();

	/* Nếu có lỗi trong quá trình thu thập thông tin */
	if (newUser == nullptr)
	{
		cout << "Tạo tài khoảng không thành công!!!\n";
	}
	else
	{
		UserManagement::getInstance().themKhachHang(newUser);
		cout << "Đã tạo tài khoảng thành công!!!" << endl;
	}
}

/* Hàm kiểm tra số điện thoại hợp lệ hay không */
bool phoneValidate(const string& phone)
{
	/* Kiểm tra phone input có đủ 10 chữ số */
	if (phone.size() != 10 || phone[0] != '0')
	{
		cout << "Số điện thoại không hợp lệ";
		return false;
	}

	/* Kiểm tra nếu input chứa ký tự khác chữ số */
	for (char c : phone)
	{
		if (isdigit(c) == false)
		{
			cout << "Số điện thoại không hợp lệ" << endl;
			return false;
		}
	}

	/* Kiểm tra số điện thoại đã được đăng ký chưa */
	if(UserManagement::getInstance().findPhone(phone) != -1)
	{
		cout << "Số điện thoại đã được đăng ký!!!" << endl;
		return false;
	}

	return true;
}

bool mailValidate(const string& mail)
{
	/* Mail không có @gmail.com và @gmail.com không phải là chuỗi kết thúc */
	if (mail.size() <= 10)
	{
		cout << "Địa chỉ mail không hợp lệ" << endl;
		return false;
	}

	string tmp = toLower(mail);
	if (tmp.rfind("@gmail.com") != (mail.size() - 10))
	{
		cout << "Địa chỉ mail không hợp lệ" << endl;
		return false;
	}
	
	/* Kiểm tra xem mail đã được đăng ký chưa */
	if (UserManagement::getInstance().findMail(tmp) != -1)
	{
		cout << "Địa chỉ mail đã được đăng ký!!!" << endl;
		return false;
	}

	/* Hợp lệ */
	return true;
}
