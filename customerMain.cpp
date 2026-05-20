#include <iostream>
#include <string>
#include <iomanip>
#include "CustomerManagement.h"
#include "users.h"
#include "common.h"

using namespace std;

enum {
	LIST_USER_E = 1,
	ADD_USER_E,
	MOD_USER_E,
	DEL_USER_E,
	FIND_USER_NUM,
	FIND_USER_NAME
};

/* Static Functions Prototype  */
static void deleteUser();
static void findUserPhone();
static void findUserName();

/* Hàm main của việc quản lý khách hàng */
void userMain()
{
	/* Lấy Users */
	CustomerManagement &Users = CustomerManagement::getInstance();

	/* Loop đến khi yêu cầu dừng */
	while (true)
	{
		/* Show Customer Menu */
		Users.Menu();
		cout << "Nhập vào chức năng: ";
		int opt = getOption();
		bool back = false;

		/* Thực hiện chức năng tương ứng */
		switch (opt)
		{
			case LIST_USER_E: Users.XuatDanhSachKH(); break;	/* Xuất tất cả khách hàng có trong hệ thống */
			case ADD_USER_E: Users.addCustomer(); break;		/* Thêm khách hàng mới */
			case MOD_USER_E: editUser(); break;					/* Chỉnh sửa thông tin khách hàng */
			case DEL_USER_E: deleteUser(); break;				/* Xóa khách hàng */
			case FIND_USER_NUM: findUserPhone(); break;			/* Tìm kiếm khách hàng theo số điện thoại */
			case FIND_USER_NAME: findUserName(); break;			/* Tìm kiếm khách hàng theo tên khách hàng */
			default:
				back = true;
				break;
		}

		/* Back về main menu*/
		if (back == true) break;
	}
}

/* Xóa Khách Hàng theo Mã KH  */
void deleteUser()
{
	CustomerManagement& Users = CustomerManagement::getInstance();
	string delID;
	cout << "Nhập vào ID khách hàng cần xóa: ";
	getline(cin, delID);
	
	/* Kiểm tra xem ID có hợp lệ hay không */
	if (ktUserID(delID) != true)
	{
		cout << "ID không hợp lệ" << endl;
		return;
	}

	/* Tìm kiếm khách hàng theo ID */
	int index = Users.findID(toUpper(delID));

	if (index != -1)
	{
		/* Tìm thấy Khách Hàng, tiến hành xóa */
		Users.XoaKhachHang(index);
		cout << "Đã xóa khách hàng có ID: " << delID << endl;
	}
	else
	{
		/* Không tìm thấy khách hàng */
		cout << "Không tìm thấy khách hàng có ID: " << delID << endl;
	}
}

/* Hàm tìm kiếm Khách Hàng theo số điện thoại */
void findUserPhone()
{
	CustomerManagement& Users = CustomerManagement::getInstance();
	string phone;
	cout << "Nhập vào số điện thoại cần tìm: ";
	getline(cin, phone);

	/* Kiểm tra số điện thoại có hợp lệ không */
	if (phone.empty() || phone.size() != 10)
	{
		cout << "Số điện thoại không hợp lệ" << endl;
		return;
	}

	/* Tìm kiếm khách hàng theo số điện thoại */
	int index = Users.findPhone(phone);

	if (index != -1)
	{
		cout << setfill('=') << setw(42) << "" << endl;
		cout << setfill(' ') << setw(12) << "" << "Thông tin khách hàng" << endl;
		cout << setfill('=') << setw(42) << "" << endl;
		/* Tìm thấy khách hàng, xuất thông tin */
		Users.getDanhSach()[index]->XuatThongTin();
	}
	else
	{
		cout << "Không tìm thấy khách hàng" << endl;
	}
}

/* Hàm tìm khách hàng theo tên */
void findUserName()
{
	string name;
	cout << "Nhập vào tên khách hàng cần tìm: ";
	getline(cin, name);

	/* Kiểm tra input hợp lệ */
	if (name.empty())
	{
		cout << "Tên không hợp lệ!!!\n";
		return;
	}

	/* Convert về lowercase */
	name = toLowerUtf8(name);

	/* Lấy Users */
	CustomerManagement& Users = CustomerManagement::getInstance();

	int index = Users.findName(name);

	if (index == -1)
	{
		cout << "Không tìm thấy khách hàng" << endl;
	}
	else
	{
		cout << setfill('=') << setw(42) << "" << endl;
		cout << setfill(' ') << setw(12) << "" << "Thông tin khách hàng" << endl;
		cout << setfill('=') << setw(42) << "" << endl;
		/* Tìm thấy khách hàng, xuất thông tin */
		Users.getDanhSach()[index]->XuatThongTin();
	}
}
