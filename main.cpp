#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <Windows.h>
#include <limits>
#include "menu.h"
#include "common.h"
#include "KhachHang.h"
#include "users.h"
#include "storeData.h"
#include "loadData.h"

#include "UserManagement.h"

using namespace std;

enum {
	EXIT_E = 0,
	CUSTOMER_E,
	BOOK_E,
	BILL_E
};

int main()
{
	/* Set up ban đầu để chương trình có thể hiểu và in ra ký tự Unicode */
	/* Note: hiện mặc định hỗ trợ hệ điều hành Window */
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);

	loadData();

	UserManagement& Users = UserManagement::getInstance();

	for (KhachHang* kh : Users.getDanhSach())
	{
		kh->XuatThongTin();
	}

	cout << "Tổng số lượng active account trong hệ thống: " << Users.getSoLuongKH() << endl;

	/* Loop đến khi exit */
	while (true)
	{
		/* Mở main menu */
		MainMenu();
		cout << "Nhập vào chức năng: ";
		int opt = getOption();

		/* Chọn chức năng */
		switch (opt)
		{
			case CUSTOMER_E: userMain(); break;	/* Quản lý khách hàng */
			case BOOK_E: /* Quản lý sách */
				break;
			case BILL_E: /* Quản lý hóa đơn */
				break;
			case EXIT_E:
				break;
			default:
				cout << "Input không hợp lệ!!!" << endl;
				break;
		}

		/* Kiểm tra nếu yêu cầu thoát */
		if (opt == EXIT_E)
			break;
	}

	cout << "Ghi dữ liệu..." << endl;
	storeCustomerData();
	cout << "Shutdown..." << endl;

	//KhachHang* kh = new KhachHang();

	//kh->XuatThongTin();
	
	/* Xuất thông tin khách hàng */
	//vector<KhachHang*> danhSachKH = Users.getDanhSach();

	
	return 0;
}