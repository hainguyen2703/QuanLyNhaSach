#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include "main.h"
#include "book_ultis.h"

using namespace std;

static void menuKho();
static void modBook();

/* Hàm main của quản lý kho */
void mainKho()
{
	while (true)
	{
		/* Show menu */
		menuKho();
		cout << "Nhập chức năng: ";
		int opt = getOption();
		bool back = false;

		switch (opt)
		{
		case 1: modBook();  break;		/* Điều chỉnh (tăng/giảm) */
		case 2: deleteBook(); break;	/* Xóa sách */
		case 0: back = true;  break;	/* Trở về main */
		default:
			cout << "Lựa chọn không hợp lệ!!!" << endl;
			break;
		}

		/* Trở về main */
		if (back == true) break;
	}
}

/* Menu chức năng kho */
void menuKho()
{
	cout << setfill('=')
		<< setw(42) << "" << endl
		<< setfill(' ') << setw(15) << "" << "Quản lý Kho" << endl
		<< setfill('=') << setw(42) << "" << endl
		<< "1. Điều chỉnh" << endl
		<< "2. Xóa" << endl
		<< "0. Thoát" << endl
		<< setw(42) << "" << endl;
}

/* Hàm điều chỉnh số lượng sách trong kho */
void modBook()
{
	cout << "Nhập vào tên sách muốn thay đổi: ";
	string name;
	if (getStringLine(name) != true)
	{
		cout << "Input không hợp lệ" << endl;
		return;
	}

	/* Tìm sách */
	vector<Book*> listBook = BookManagement::getInstance().findName(name);

	string isbn;

	/* Không tìm thấy sách */
	if (listBook.empty())
	{
		cout << "Không tìm thấy sách trong kho" << endl;
		return;
	}
	else if (listBook.size() > 1)
	{
		/* Có ít nhất 2 sách trùng tên */
		/* Tạo khung info sách */
		khungBookInfo();
		/* In thông tin sách */
		int count = 1;
		for (Book* book : listBook)
		{
			cout << left << setfill(' ') << setw(3) << count++;
			cout << "|";
			book->XuatThongTin();
			cout << endl << setfill('_') << setw(155) << "" << endl;
		}
		cout << "Chọn sách muốn xóa theo index (No.): ";
		int opt = getOption();
		if (opt < 1 || opt > listBook.size())
		{
			cout << "Lựa chọn không hợp lệ" << endl;
			return;
		}
		else
			/* Lấy isbn */
			isbn = listBook[opt - 1]->getIsbn();
	}
	else
	{
		/* Lấy isbn */
		isbn = listBook[0]->getIsbn();
	}

	cout << "Nhập vào số lượng sách thay đổi: ";
	int soLuong;
	cin >> soLuong;
	if (cin.fail())
	{
		cin.clear();              // xóa trạng thái lỗi
		cin.ignore(1000, '\n');   // bỏ ký tự sai trong buffer
		cout << "Số lượng không hợp lệ!!" << endl;
		return;
	}

	/* Làm sạch buffer */
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	/* Cập nhật */
	BookManagement::getInstance().getBookByIsbn(isbn)->setSoLuong(soLuong, CAP_NHAT);
	BookManagement::storeToCsv();
	cout << "Cập nhật số lượng thành công" << endl;
}