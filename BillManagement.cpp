#include <iostream>
#include <string>
#include "BillManagement.h"
#include "BookManagement.h"
#include "CustomerManagement.h"
#include "customer_ultis.h"
#include "book_ultis.h"
#include "common.h"

using namespace std;

/* Hàm lấy instance của BillManagement */
BillManagement& BillManagement::getInstance()
{
	static BillManagement instance;
	return instance;
}

void BillManagement::taoHoaDon()
{
	/* Lấy mã khách hàng */
	cout << "Nhập vào mã khách hàng: ";
	string maKH;
	if (getStringLine(maKH) != true)
		return;

	if (ktUserID(maKH) != true)
	{
		cout << "Input không hợp lệ" << endl;
		return;
	}

	/* Kiểm tra nếu lấy được thông tin khách hàng */
	if (CustomerManagement::getInstance().findID(maKH) == -1)
	{
		cout << "Không tìm thấy khách hàng có mã " << maKH << endl;
		return;
	}

	/* Lấy ngày lập hóa đơn */
	Date date;
	cout << "Ngày xuất hóa đơn: " << endl;
	cin >> date;

	/* Kiểm tra input */
	if (!cin)
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Ngày không hợp lệ" << endl;
		return;
	}
	else
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

	/* Kiểm tra ngày */
	if (validateDate(date) != true)
	{
		cout << "Ngày không hợp lệ" << endl;
		return;
	}

	/* Tạo hóa đơn chưa có item */
	HoaDon* hd = new HoaDon(maKH, date);

	/* Thêm item vào hóa đơn */
	/* Show list book hiện tại trong nhà sách */
	BookManagement::getInstance().XuatDanhSachBooks();

	bool exit = false;
	/* Loop nhập sách - số lượng */
	while (true)
	{
		cout << "Nhập mã isbn: ";
		string isbn;
		if (getStringLine(isbn) != true)
		{
			if (isbn == "\n")
				break;
			else 
				continue;
		}

		/* Kiểm tra input */
		if (isbnValidate(isbn) != true || BookManagement::getInstance().findISBN(isbn) == -1)
		{
			cout << "Input không hợp lệ" << endl;
			continue;
		}

		/* Lấy book */
		int remain = BookManagement::getInstance().getBookByIsbn(isbn)->getSoLuong();
		bool exit = false;
		cout << "Nhập vào số lượng: ";
		int soLuong;
		while (true)
		{
			cin >> soLuong;
			if (cin.fail())
			{
				cin.clear();              // xóa trạng thái lỗi
				cin.ignore(1000, '\n');   // bỏ ký tự sai trong buffer
				cout << "Nhập sai, vui lòng nhập chữ số: ";
				continue;
			}

			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			/* Kiểm tra nếu input âm */
			if (soLuong <= 0)
			{
				exit = true;
				break; /* Thoát inner while loop */
			}
			/* Kiểm tra nếu số lượng trong kho không đủ */
			else if (soLuong > remain)
			{
				cout << "Không đủ sách trong kho, số sách còn lại: " << remain << endl;
				cout << "Vui lòng nhập lại số lượng sách: ";
				continue;
			}
			else
			{
				/* Add item vào hóa đơn */
				hd->addItem({ isbn, soLuong });
				break;
			}
		}

		if (exit == true) break; /* Dừng chọn isbn - số lượng */
	}

	/* Set hóa đơn nếu được */
	if (hd->setMaHD() != true)
	{
		delete hd;
	}
	else
	{
		/* In hóa đơn */
		hd->xuatHoaDon();
		/* Xác nhận */
		cout << "Xác nhận hóa đơn (Y/N): ";
		char ack;
		cin >> ack;

		if (ack == 'Y' || ack == 'y')
		{
			HoaDon::increaseMaHD();

			/* Thêm vào list hóa đơn */
			this->listHoaDon.push_back(hd);
		}
		else
		{
			delete hd;
		}

	}
}