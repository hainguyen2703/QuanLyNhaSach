#include <iostream>
#include <string>
#include <iomanip>
#include "menu.h"
#include "CustomerManagement.h"
#include "common.h"
#include "users.h"

using namespace std;

enum {
	USER_NAME_E = 1,
	USER_PHONE_E,
	USER_ADDRESS_E,
	USER_MAIL_E,
	USER_TYPE_E
};

/* Static function prototyp */
static void editUserName(const int& index);
static void editUserPhone(const int& index);
static void editUserAddress(const int& index);
static void editUserMail(const int& index);
static void editUserType(const int& index);

/* Hàm chỉnh sửa thông tin Khách hàng */
void editUser()
{
	string id;
	cout << "Nhập vào ID khách hàng cần sửa: ";
	getline(cin, id);

	/* Kiểm tra ID nhập vào có hợp lệ hay không */
	if (ktUserID(id) != true)
	{
		cout << "ID không hợp lệ" << endl;
		return;
	}

	/* Lấy Users */
	CustomerManagement& Users = CustomerManagement::getInstance();

	/* Tìm kiếm khách hàng theo ID */
	int index = Users.findID(toUpper(id));

	/* Xuất thông tin nếu tìm thấy khách hàng */
	if (index == -1)
	{
		/* Không tìm thấy khách hàng */
		cout << "Không tìm thấy khách hàng có ID: " << id << endl;
		return;
	}

	/* Xuất thông tin khách hàng */
	cout << setfill('=') << setw(42) << "" << endl;
	cout << setfill(' ') << setw(12) << "" << "Thông tin khách hàng" << endl;
	cout << setfill('=') << setw(42) << "" << endl;
	/* Tìm thấy khách hàng, xuất thông tin */
	Users.getDanhSach()[index]->XuatThongTin();
	cout << setfill('_') << setw(42) << "" << endl;

	while (true)
	{
		/* Xuất menu edit */
		editUserMenu();

		cout << "Nhập vào thông tin cần thay đổi: ";
		/* Lấy thông tin cần cập nhật */
		int opt = getOption();
		bool back = false;

		/* Thực hiện chức năng tương ứng */
		switch (opt)
		{
			case USER_NAME_E: editUserName(index); break;			/* Chỉnh sửa tên khách hàng */
			case USER_PHONE_E: editUserPhone(index); break;			/* Chỉnh sửa số điện thoại */
			case USER_ADDRESS_E: editUserAddress(index); break;		/* Chỉnh sửa địa chỉ */
			case USER_MAIL_E: editUserMail(index); break;			/* Chỉnh sửa email */
			case USER_TYPE_E: editUserType(index); break;			/* Chỉnh sửa loại thẻ */
			default:
				back = true;
				break;
		}

		/* Back về main menu*/
		if (back == true) break;

		cout << setfill('_') << setw(42) << "" << endl;
		Users.getDanhSach()[index]->XuatThongTin();
		cout << setfill('_') << setw(42) << "" << endl;
	}
}

/* Thay đổi tên khách hàng */
void editUserName(const int &index)
{
	string name;
	cout << "Nhập vào tên khách hàng mới: ";
	getline(cin, name);

	/* Kiểm tra input hợp lệ */
	if (name.empty())
	{
		cout << "Tên không hợp lệ!!!\n";
		return;
	}

	/* Cập nhật tên khách hàng */
	CustomerManagement::getInstance().getDanhSach()[index]->setName(name);
	cout << "Đã cập nhật tên khách hàng thành công!" << endl;
}

/* Thay đổi số điện thoại khách hàng */
void editUserPhone(const int& index)
{
	string phone;
	cout << "Nhập vào số điện thoại mới: ";
	getline(cin, phone);

	/* Kiểm tra số điện thoại có hợp lệ không */
	if(phoneValidate(phone) != true)
	{
		cout << "Số điện thoại không hợp lệ" << endl;
		return;
	}

	/* Cập nhật số điện thoại khách hàng */
	CustomerManagement::getInstance().getDanhSach()[index]->setPhone(phone);
	cout << "Đã cập nhật số điện thoại khách hàng thành công!" << endl;
}

/* Thay đổi địa chỉ khách hàng */ 
void editUserAddress(const int& index)
{
	string address;
	cout << "Nhập vào địa chỉ mới: ";
	getline(cin, address);
	/* Kiểm tra địa chỉ có hợp lệ không */
	if (address.empty())
	{
		cout << "Địa chỉ không hợp lệ" << endl;
		return;
	}
	/* Cập nhật địa chỉ khách hàng */
	CustomerManagement::getInstance().getDanhSach()[index]->setAddress(address);
	cout << "Đã cập nhật địa chỉ khách hàng thành công!" << endl;
}

/* Thay đổi email khách hàng */
void editUserMail(const int& index)
{
	CustomerManagement& Users = CustomerManagement::getInstance();
	string mail;
	cout << "Nhập vào email mới: ";
	getline(cin, mail);

	if(mailValidate(mail) != true)
	{
		cout << "Email không hợp lệ" << endl;
		return;
	}

	/* Cập nhật email khách hàng */
	Users.getDanhSach()[index]->setMail(mail);
	cout << "Đã cập nhật email khách hàng thành công!" << endl;
}

/* Thay đổi loại thẻ khách hàng */
void editUserType(const int& index)
{
	int type;
	cout << "Nhập vào loại thẻ mới(0: Normal, 1: VIP): ";
	cin >> type;
	cin.ignore(100, '\n');
	if (type != 0 && type != 1)
	{
		cout << "Loại thẻ không hợp lệ!!" << endl;
		return;
	}
	/* Cập nhật loại thẻ khách hàng */
	CustomerManagement::getInstance().getDanhSach()[index]->setType(type);
	cout << "Đã cập nhật loại thẻ khách hàng thành công!" << endl;
}