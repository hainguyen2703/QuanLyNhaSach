#include <iostream>
#include <string>
#include "KhachHang.h"
#include "UserManagement.h"
#include "userRegister.h"
#include "users.h"
#include "menu.h"
#include "common.h"

using namespace std;

/* Hàm main của việc quản lý khách hàng */
void userMain()
{
	UserManagement& Users = UserManagement::getInstance();

	/* Loop đến khi yêu cầu dừng */
	while (true)
	{
		/* Show Customer Menu */
		CustomerMenu();
		cout << "Nhập vào chức năng: ";
		int opt = getOption();

		switch (opt)
		{
		case LIST_E:
		case ADD_E: createUser(Users); break;	/* Thêm khách hàng mới */
		case MOD_E:
		case DEL_E:
		case FIND_NUM:
		case FIND_NAME:
		case BACK_E:
			break;
		}

		if (opt == BACK_E)
		{
			break;
		}
	}

	//cout << "Số lượng khách hàng trong hệ thống: " << UserManagement::getSoLuongKH() << endl;

	/* Xuất thông tin khách hàng */
}