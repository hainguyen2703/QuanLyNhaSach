#include <iostream>
#include <string>
#include <iomanip>
#include "KhachHang.h"
#include "common.h"

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
}
