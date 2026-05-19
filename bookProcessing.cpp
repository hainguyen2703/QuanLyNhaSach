#include "book_ultis.h"
#include "common.h"

using namespace std;

enum {
	LIST_BOOK_E = 1,
	ADD_BOOK_E,
	MOD_BOOK_E,
	DEL_BOOK_E,
	FIND_BOOK_ISBN,
	FIND_BOOK_NAME,
};

/* Static function prototype */
static void findBookISBN();
static void findBookName();

/* Hàm main của việc quản lý sách */
void bookMain()
{
	/* Lấy object Books */
	BookManagement &Books = BookManagement::getInstance();

	/* Loop đến khi yêu cầu dừng */
	while (true)
	{
		/* Show menu quản lý sách */
		Books.bookMenu();

		cout << "Nhập vào chức năng: ";
		int opt = getOption();
		bool back = false;

		switch (opt)
		{
			case LIST_BOOK_E: Books.XuatDanhSachBooks(); break;		/* Xuất tất cả sách có trong hệ thống */
			case ADD_BOOK_E: Books.addBook(); break;				/* Thêm sách mới */
			case MOD_BOOK_E:  break;								/* Chỉnh sửa thông tin sách */
			case DEL_BOOK_E:  break;								/* Xóa sách */
			case FIND_BOOK_ISBN: findBookISBN(); break;				/* Tìm kiếm sách theo ISBN */
			case FIND_BOOK_NAME: findBookName(); break;				/* Tìm kiếm sách theo tên */
			default:
				back = true;
				break;
		}

		/* Back về main menu*/
		if (back == true) break;
	}
}

/* Hàm tìm và xuất thông tin sách theo ISBN */
void findBookISBN()
{
	string isbn;
	cout << "Nhập vào ISBN cần tìm: ";
	getline(cin, isbn);

	/* Kiểm tra nếu ISBN không hợp lệ */
	if (isbnValidate(isbn) != true)
	{
		cout << "ISBN không hợp lệ!!\n";
		return;
	}

	/* Tìm kiếm theo ISBN */
	BookManagement &Books = BookManagement::getInstance();
	int index = Books.findISBN(isbn);

	/* Nếu tìm thấy, xuất thông tin sách*/
	if (index != -1)
	{
		cout << setfill('=')
			<< setw(42) << "" << endl
			<< setfill(' ') << setw(12) << "" << "Thông tin sách" << endl
			<< setfill('=') << setw(42) << "" << endl;
		Books.getDanhSachBooks()[index]->XuatThongTin();
		cout << setfill('=') << setw(42) << "" << endl;
	}
	else
		cout << "Không tìm thấy sách có ISBN: " << isbn << endl;
}

/* Hàm tìm và xuất thông tin sách theo tên sách */
void findBookName()
{
	string name;
	cout << "Nhập vào tên sách cần tìm: ";
	getline(cin, name);

	/* Kiểm tra input */
	if (isAllBlank(name))
	{
		cout << "Tên sách không hợp lệ" << endl;
		return;
	}

	/* Tìm sách theo tên */
	int index = BookManagement::getInstance().findName(toLowerUtf8(name));
	if (index != -1)
	{
		cout << setfill('=')
			<< setw(42) << "" << endl
			<< setfill(' ') << setw(12) << "" << "Thông tin sách" << endl
			<< setfill('=') << setw(42) << "" << endl;
		BookManagement::getInstance().getDanhSachBooks()[index]->XuatThongTin();
		cout << setfill('=') << setw(42) << "" << endl;
	}
	else
		cout << "Không tìm thấy sách " << name << endl;
}