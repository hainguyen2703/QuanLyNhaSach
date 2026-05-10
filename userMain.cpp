#include <iostream>
#include <string>
#include "KhachHang.h"
#include "UserManagement.h"
#include "userRegister.h"
#include "users.h"

using namespace std;

void userMain()
{
	UserManagement& Users = UserManagement::getInstance();

	createUser(Users);

	cout << "Số lượng khách hàng trong hệ thống: " << UserManagement::getSoLuongKH() << endl;

	/* Xuất thông tin khách hàng */
}