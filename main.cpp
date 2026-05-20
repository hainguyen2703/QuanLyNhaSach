#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <Windows.h>
#include <limits>
#include <iomanip>
#include "main.h"
#include "common.h"
#include "KhachHang.h"
#include "CustomerManagement.h"
#include "BookManagement.h"

using namespace std;

enum {
	EXIT_E = 0,
	CUSTOMER_E,
	BOOK_E,
	BILL_E
};

/* Static function prototype */
static void storeData();
static void showMainMenu();

int main()
{
	/* Set up ban đầu để chương trình có thể hiểu và in ra ký tự Unicode */
	/* Note: hiện mặc định hỗ trợ hệ điều hành Window */
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);

	/* load dữ liệu từ csv */
	CustomerManagement::loadFromCsv();
	BookManagement::loadFromCsv();

	/* Loop đến khi exit */
	while (true)
	{
		/* Mở main menu */
		showMainMenu();
		cout << "Nhập vào chức năng: ";
		int opt = getOption();

		/* Chọn chức năng */
		switch (opt)
		{
			case CUSTOMER_E: userMain(); break;	/* Quản lý khách hàng */
			case BOOK_E: bookMain(); break;		/* Quản lý sách */
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
	storeData();
	cout << "Shutdown..." << endl;
	
	return 0;
}

/* Ham trinh chieu main menu */
void showMainMenu()
{
	cout << setfill('=')
		<< setw(42) << "" << endl
		<< setfill(' ') << setw(12) << "" << "Quản Lý Nhà Sách" << endl
		<< setfill('=') << setw(42) << "" << endl
		<< "1. Quản lý khách hàng" << endl
		<< "2. Quản lý sách" << endl
		<< "3. Quản lý hóa đơn bán hàng" << endl
		<< "0. Thoát" << endl
		<< setw(42) << "" << endl;
}

/* Ghi dữ liệu xuống file csv */
void storeData()
{
	cout << "Tiến hành lưu thông tin khách hàng..." << endl;
	CustomerManagement::storeToCsv();
	cout << "Tiến hành lưu thông tin Sách..." << endl;
	BookManagement::storeToCsv();
}