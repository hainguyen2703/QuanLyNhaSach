#include "CustomerManagement.h"
#include "customer_ultis.h"

using namespace std;

enum {
	LIST_USER_E = 1,
	ADD_USER_E,
	MOD_USER_E,
	DEL_USER_E,
	FIND_USER_NUM,
	FIND_USER_NAME
};

enum {
	USER_NAME_E = 1,
	USER_PHONE_E,
	USER_ADDRESS_E,
	USER_MAIL_E,
	USER_TYPE_E
};

/* Static Functions Prototype  */
static void deleteUser();
static void findUserPhone();
static void findUserName();
static void editUser();
static void khungInfoKH();

/* Hàm main của việc quản lý khách hàng */
void customerMain()
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
			case 0: back = true; break;							/* Trở về main menu */
			default:
				cout << "Lựa chọng không hợp lệ" << endl;
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
	/* Kiểm tra xem ID có hợp lệ hay không */
	if (getStringLine(delID) != true || ktUserID(delID) != true)
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
	/* Kiểm tra số điện thoại có hợp lệ không */
	if (getStringLine(phone) != true || phone.size() != 10)
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
	if(getStringLine(name) != true)
	{
		cout << "Tên không hợp lệ!!!\n";
		return;
	}

	/* Convert về lowercase */
	name = toLowerUtf8(name);

	/* Lấy Users */
	CustomerManagement& Users = CustomerManagement::getInstance();

	vector<KhachHang*>  list_kh = Users.findName(toLowerUtf8(name));

	if (list_kh.empty())
	{
		cout << "Không tìm thấy khách hàng" << endl;
	}
	else if (list_kh.size() > 1)
	{
		/* Nhiều hơn 1 khách hàng */
		khungInfoKH();
		for (KhachHang* kh : list_kh)
		{
			/* xuất thông tin */
			kh->XuatThongTin();
			cout << setfill('_') << setw(164) << "" << endl;
		}
	}
	else
	{
		khungInfoKH();
		/* xuất thông tin */
		list_kh[0]->XuatThongTin();
		cout << setfill('_') << setw(164) << "" << endl;
	}
}

void khungInfoKH()
{
	cout << setfill('=') << setw(164) << "" << endl;
	print_utf8_left("Mã khách hàng", 15);
	cout << "|";
	print_utf8_left("Tên khách hàng", 30);
	cout << "|";
	print_utf8_left("Số điện thoại", 15);
	cout << "|";
	print_utf8_left("Email", 30);
	cout << "|";
	print_utf8_left("Địa chỉ", 40);
	cout << "|";
	print_utf8_left("Ngày đăng ký", 15);
	cout << "|";
	print_utf8_left("Loại thẻ", 12);
	cout << "|" << endl;
	cout << setfill('=') << setw(164) << "" << endl;
}

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
	khungInfoKH();
	kh->XuatThongTin();
	cout << setfill('=') << setw(164) << "" << endl;

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
		case USER_PHONE_E: editUserPhone(kh); break;		/* Chỉnh sửa số điện thoại */
		case USER_ADDRESS_E: editUserAddress(kh); break;	/* Chỉnh sửa địa chỉ */
		case USER_MAIL_E: editUserMail(kh); break;			/* Chỉnh sửa email */
		case USER_TYPE_E: editUserType(kh); break;			/* Chỉnh sửa loại thẻ */
		case 0: back = true; break;							/* Trở về menu quản lý khách hàng */
		default:
			cout << "Lựa chọn không hợp lệ" << endl;
			break;
		}

		/* Back về main menu*/
		if (back == true)
		{
			/* Lưu xuống csv */
			CustomerManagement::storeToCsv();
			break;
		}

		khungInfoKH();
		Users.getDanhSach()[index]->XuatThongTin();
		cout << setfill('=') << setw(164) << "" << endl;
	}
}
