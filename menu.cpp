#include <iostream>
#include <string>
#include <iomanip>
#include "menu.h"

using namespace std;

/* Menu chức năng edit thông tin khách hàng */
void editUserMenu()
{
	cout << setfill('=') << setw(42) << "" << endl;
	cout << setfill(' ') << setw(10) << "" << "Chỉnh sửa thông tin" << endl;
	cout << setfill('=') << setw(42) << "" << endl;
	cout << "1. Chỉnh sửa tên khách hàng" << endl;
	cout << "2. Chỉnh sửa số điện thoại" << endl;
	cout << "3. Chỉnh sửa địa chỉ" << endl;
	cout << "4. Chỉnh sửa mail" << endl;
	cout << "5. Chỉnh sửa loại thẻ" << endl;
	cout << "0. Thoát" << endl;
	cout << setw(42) << "" << endl;
}