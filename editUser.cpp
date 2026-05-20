#include <iostream>
#include <string>
#include <iomanip>
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
static void editUserMenu();
static void editUserName(KhachHang* kh);
static void editUserPhone(KhachHang* kh);
static void editUserAddress(KhachHang* kh);
static void editUserMail(KhachHang* kh);
static void editUserType(KhachHang* kh);

/* Hàm chỉnh sửa thông tin Khách hàng */
void editUser()
{
	string id;
	cout << "Nhập vào ID khách hàng cần sửa: ";
	/* Kiểm tra ID nhập vào có hợp lệ hay không */
	if (getStringLine(id) != true || ktUserID(id) != true)
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

	/* Lấy khách hàng ra */
	KhachHang* kh = CustomerManagement::getInstance().getDanhSach()[index];

	/* Xuất thông tin khách hàng */
	kh->XuatThongTin();

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
			case USER_NAME_E: editUserName(kh); break;			/* Chỉnh sửa tên khách hàng */
			case USER_PHONE_E: editUserPhone(kh); break;			/* Chỉnh sửa số điện thoại */
			case USER_ADDRESS_E: editUserAddress(kh); break;		/* Chỉnh sửa địa chỉ */
			case USER_MAIL_E: editUserMail(kh); break;			/* Chỉnh sửa email */
			case USER_TYPE_E: editUserType(kh); break;			/* Chỉnh sửa loại thẻ */
			default:
				back = true;
				break;
		}

		/* Back về main menu*/
		if (back == true)
		{
			/* Lưu xuống csv */
			CustomerManagement::storeToCsv();
			break;
		}

		cout << setfill('_') << setw(42) << "" << endl;
		Users.getDanhSach()[index]->XuatThongTin();
		cout << setfill('_') << setw(42) << "" << endl;
	}
}

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

/* Thay đổi tên khách hàng */
void editUserName(KhachHang* kh)
{
	string name;
	cout << "Nhập vào tên khách hàng mới: ";
	if(getStringLine(name) != true)
	{
		cout << "Tên không hợp lệ!!!\n";
		return;
	}

	/* Cập nhật tên khách hàng */
	kh->setName(name);
	cout << "Đã cập nhật tên khách hàng thành công!" << endl;
}

/* Thay đổi số điện thoại khách hàng */
void editUserPhone(KhachHang* kh)
{
	string phone;
	cout << "Nhập vào số điện thoại mới: ";
	/* Kiểm tra số điện thoại có hợp lệ không */
	if(getStringLine(phone) != true || phoneValidate(phone) != true)
	{
		cout << "Số điện thoại không hợp lệ" << endl;
		return;
	}

	/* Cập nhật số điện thoại khách hàng */
	kh->setPhone(phone);
	cout << "Đã cập nhật số điện thoại khách hàng thành công!" << endl;
}

/* Thay đổi địa chỉ khách hàng */ 
void editUserAddress(KhachHang* kh)
{
	string address;
	cout << "Nhập vào địa chỉ mới: ";
	if(getStringLine(address) != true)
	{
		cout << "Địa chỉ không hợp lệ" << endl;
		return;
	}
	
	/* Cập nhật địa chỉ khách hàng */
	kh->setAddress(address);
	cout << "Đã cập nhật địa chỉ khách hàng thành công!" << endl;
}

/* Thay đổi email khách hàng */
void editUserMail(KhachHang* kh)
{
	CustomerManagement& Users = CustomerManagement::getInstance();
	string mail;
	cout << "Nhập vào email mới: ";
	if(getStringLine(mail) != true || mailValidate(mail) != true)
	{
		cout << "Email không hợp lệ" << endl;
		return;
	}

	/* Cập nhật email khách hàng */
	kh->setMail(mail);
	cout << "Đã cập nhật email khách hàng thành công!" << endl;
}

/* Thay đổi loại thẻ khách hàng */
void editUserType(KhachHang* kh)
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
	kh->setType(type);
	cout << "Đã cập nhật loại thẻ khách hàng thành công!" << endl;
}