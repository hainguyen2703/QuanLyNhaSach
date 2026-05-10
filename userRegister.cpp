#include <iostream>
#include <string>
#include <cctype>
#include <iomanip>
#include "KhachHang.h"
#include "common.h"
#include "userRegister.h"

using namespace std;

/* Static function prototype */

/* Hàm yêu cầu user đưa input để tạo tài khoảng */
bool createUser()
{
	/* Thông tin cần điền: 
	 * 1. Họ tên 
	 * 2. Ngày tháng năm sinh
	 * 3. Số điện thoại
	 * 4. Mail
	 * 5. Địa chỉ 
	 * 6. Loại thẻ (Optional ??) */
	string hoten;	/* Biến chứa tên khách hàng */

	/* 1. Họ tên */
	cout << setw(20) << setfill('*') << endl;
	cout << "Tạo tài khoảng" << endl;
	cout << setw(20) << setfill('*') << endl;
	cout << "Họ tên khách hàng: " << endl;
	getline(cin, hoten);
	/* Kiểm tra nếu chuỗi input toàn khoảng trắng */
	if (isAllBlank(hoten)) return false;

	/* 2. Ngày tháng năm sinh */
	Date birth;
	cout << "Ngày tháng năm sinh (dd/mm/yyyy): ";
	cin >> birth;
	/* Kiểm tra date input */
	if (!cin)
	{
		cout << "Ngày sinh không hợp lệ!!" << endl;
		/* Xóa fail bit */
		cin.clear(); 
		/* Clear input cache */
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}

	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	/* 3. Số điện thoại */
	string phone;
	cout << "Số điện thoại: ";
	getline(cin, phone);
	/* Kiểm tra phone input */
	if (phone.size() != 10 || phone[0] != '0')
	{
		cout << "Số điện thoại không hợp lệ";
	}
	/* Kiểm tra nếu input chứa ký tự khác chữ số */
	for (char c : phone)
	{
		if (isdigit(c) == false)
		{
			cout << "Số điện thoại không hợp lệ" << endl;
			break;
		}
	}

	/* 4. Mail */
	string mail;
	cout << "Mail: ";
	getline(cin, mail);
	/* Kiểm tra mail input */
	/* Mail không có @gmail.com và @gmail.com không phải là chuỗi kết thúc */
	if (mail.size() <= 10 || 
		mail.rfind("@gmail.com") != (mail.size() - 10))
	{
		cout << "Địa chỉ mail không hợp lệ" << endl;
	}

	/* 5. Địa chỉ */
	string address;
	cout << "Địa chỉ: ";
	getline(cin, address);
	/* Kiểm tra địa chỉ */
	if (address.empty())
	{
		cout << "Địa chỉ không hợp lệ!!\n";
	}

	/* 6. Loại thẻ */
	int the;
	cout << "Loại thẻ: ";
	cin >> the;
	cin.ignore(100, '\n');
	if (the != 0 || the != 1)
	{
		cout << "Không hợp lệ!!" << endl;
	}

	return true;
}
