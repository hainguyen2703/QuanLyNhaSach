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

enum {
	ISBN = 1,
	NAME,
	AUTHOR,
	NXB,
	CATEGORY,
	YEAR,
	QUANTITY,
	IMPORT_PRICE,
	SELL_PRICE,
};

/* Static function prototype */
static void findBookISBN();
static void findBookName();
static void editBook();

/* Hàm main của việc quản lý sách */
void bookMain()
{
	/* Lấy object Books */
	BookManagement &Books = BookManagement::getInstance();

	/* Loop đến khi yêu cầu dừng */
	while (true)
	{
		/* Show menu quản lý sách */
		Books.Menu();

		cout << "Nhập vào chức năng: ";
		int opt = getOption();
		bool back = false;

		switch (opt)
		{
			case LIST_BOOK_E: Books.XuatDanhSachBooks(); break;		/* Xuất tất cả sách có trong hệ thống */
			case ADD_BOOK_E: Books.addBook(); break;				/* Thêm sách mới */
			case MOD_BOOK_E: editBook(); break;						/* Chỉnh sửa thông tin sách */
			case DEL_BOOK_E: deleteBook(); break;					/* Xóa sách */
			case FIND_BOOK_ISBN: findBookISBN(); break;				/* Tìm kiếm sách theo ISBN */
			case FIND_BOOK_NAME: findBookName(); break;				/* Tìm kiếm sách theo tên */
			case 0: back = true; break;								/* Trở về main menu */
			default:
				cout << "Lựa chọn không hợp lệ" << endl;
				break;
		}

		/* Back về main menu*/
		if (back == true) break;
	}
}

void khungBookInfo()
{
	cout << setfill('=') << setw(155) << "" << endl;
	cout << left << setfill(' ') << setw(3) << "No.";
	cout << "|";
	print_utf8_left("ISBN", 15);
	cout << "|";
	print_utf8_left("Tên sách", 25);
	cout << "|";
	print_utf8_left("Tác giả", 20);
	cout << "|";
	print_utf8_left("NXB", 20);
	cout << "|";
	print_utf8_left("Năm XB", 10);
	cout << "|";
	print_utf8_left("Thể loại", 15);
	cout << "|";
	print_utf8_left("Giá nhập", 15);
	cout << "|";
	print_utf8_left("Giá bán", 15);
	cout << "|";
	print_utf8_left("Số lượng", 15);
	cout << endl;
	cout << setfill('=') << setw(155) << "" << endl;
}

/* Hàm tìm và xuất thông tin sách theo ISBN */
void findBookISBN()
{
	string isbn;
	cout << "Nhập vào ISBN cần tìm: ";
	/* Kiểm tra nếu ISBN không hợp lệ */
	if (getStringLine(isbn) != true || isbnValidate(isbn) != true)
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
		khungBookInfo();
		cout << left << setfill(' ') << setw(3) << 1;
		cout << "|";
		Books.getDanhSachBooks()[index]->XuatThongTin();
		cout << endl << setfill('=') << setw(155) << "" << endl;
	}
	else
		cout << "Không tìm thấy sách có ISBN: " << isbn << endl;
}

/* Hàm tìm và xuất thông tin sách theo tên sách */
void findBookName()
{
	string name;
	cout << "Nhập vào tên sách cần tìm: ";
	if(getStringLine(name) != true)
	{
		cout << "Tên sách không hợp lệ" << endl;
		return;
	}

	/* Tìm sách theo tên */
	vector<Book*> list_book = BookManagement::getInstance().findName(toLowerUtf8(name));
	if (list_book.empty())
		cout << "Không tìm thấy sách " << name << endl;
	else
	{
		/* Tạo khung info sách */
		khungBookInfo();
		/* In thông tin sách */
		int count = 1;
		for (Book* book : list_book)
		{
			cout << left << setfill(' ') << setw(3) << count++;
			cout << "|";
			book->XuatThongTin();
			cout << endl << setfill('_') << setw(155) << "" << endl;
		}
	}
		
}

/* Hàm xóa book khỏi nhà sách theo tên sách */
void deleteBook()
{
	cout << "Nhập vào tên sách muốn xóa: ";
	string bookName;
	if (getStringLine(bookName) != true)
	{
		cout << "Không tìm thấy sách" << endl;
		return;
	}

	/* Tìm sách theo tên sách */
	vector<Book*> list_book = BookManagement::getInstance().findName(toLowerUtf8(bookName));

	int index = -1;

	/* Kiểm tra nếu không tìm thấy sách*/
	if (list_book.empty())
	{
		cout << "Không tìm thấy sách" << endl;
		return;
	}
	else if (list_book.size() > 1)
	{
		/* Có ít nhất 2 sách trùng tên */
		/* Tạo khung info sách */
		khungBookInfo();
		/* In thông tin sách */
		int count = 1;
		for (Book* book : list_book)
		{
			cout << left << setfill(' ') << setw(3) << count++;
			cout << "|";
			book->XuatThongTin();
			cout << endl << setfill('_') << setw(155) << "" << endl;
		}
		cout << "Chọn sách muốn xóa theo index (No.): ";
		int opt = getOption();
		if (opt < 1 || opt > list_book.size())
		{
			cout << "Lựa chọn không hợp lệ" << endl;
			return;
		}
		else
		{
			/* Chỉ có 1 sách nên lấy index từ isbn */
			index = BookManagement::getInstance().findISBN(list_book[opt - 1]->getIsbn());
		}
	}
	else
	{
		/* Chỉ có 1 sách nên lấy index từ isbn */
		index = BookManagement::getInstance().findISBN(list_book[0]->getIsbn());
	}

	/* Kiểm tra nếu sách có thể xóa được 
	 * Điều kiện: Không thể xóa sách có số lượng tồn kho != 0 */
	if (BookManagement::getInstance().getDanhSachBooks()[index]->getSoLuong() != 0)
	{
		cout << "Không thể xóa sách vì vẫn còn tồn kho!!!" << endl;
	}
	else
	{
		/* Xác nhận lại */
		khungBookInfo();
		cout <<left << setfill(' ') << setw(3) << 1;
		cout << "|";
		BookManagement::getInstance().getDanhSachBooks()[index]->XuatThongTin();
		cout << endl << setfill('_') << setw(155) << "" << endl;

		cout << "Xác nhận xóa (y/n): ";
		char ack;
		cin >> ack;

		/* Làm sạch buffer */
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		/* Kiểm tra nếu xác nhận tạo hóa đơn */
		if (ack == 'Y' || ack == 'y')
		{
			/* Xóa sách */
			BookManagement::getInstance().removeBook(index);
			cout << "Đã xóa sách!!!" << endl;
		}
	}
}

/* Hàm edit thông tin book */
void editBook()
{
	cout << "Nhập vào tên sách cần sửa: ";
	string name;
	/* Kiểm tra input có hợp lệ không */
	if (getStringLine(name) != true)
	{
		cout << "Không tìm thấy sách" << endl;
		return;
	}

	/* Tìm sách */
	vector<Book*> list_book = BookManagement::getInstance().findName(toLowerUtf8(name));
	
	int index;

	/* Kiểm tra nếu tìm thấy sách */
	if (list_book.empty())
	{
		cout << "Không tìm thấy sách" << endl;
		return;
	}
	else if (list_book.size() > 1)
	{
		/* Có ít nhất 2 sách trùng tên */
		/* Tạo khung info sách */
		khungBookInfo();
		/* In thông tin sách */
		int count = 1;
		for (Book* book : list_book)
		{
			cout << left << setfill(' ') << setw(3) << count++;
			cout << "|";
			book->XuatThongTin();
			cout << endl << setfill('_') << setw(155) << "" << endl;
		}
		cout << "Chọn sách muốn sửa theo index (No.): ";
		int opt = getOption();
		if (opt < 1 || opt > list_book.size())
		{
			cout << "Lựa chọn không hợp lệ" << endl;
			return;
		}
		else
			/* Lấy index từ isbn */
			index = BookManagement::getInstance().findISBN(list_book[opt - 1]->getIsbn());
	}
	else
	{
		/* Chỉ có 1 sách nên lấy index từ isbn */
		index = BookManagement::getInstance().findISBN(list_book[0]->getIsbn());
	}

	/* Lấy book ra */
	Book* book = BookManagement::getInstance().getDanhSachBooks()[index];

	/* Xuất thông tin sách trước khi sửa */
	/* Tạo khung info sách */
	khungBookInfo();
	cout << left << setfill(' ') << setw(3) << "1" << "|";
	book->XuatThongTin();
	cout << endl << setfill('_') << setw(155) << "" << endl;

	while (true)
	{
		editBookMenu();
		cout << "Nhập thông tin cần sửa: ";
		int opt = getOption();
		bool back = false;

		switch (opt)
		{
		case ISBN: updateISBN(book);  break;			/* Cập nhật isbn */
		case NAME: updateBookName(book); break;			/* Cập nhật tên sách */
		case AUTHOR: updateAuthor(book); break;			/* Cập nhật tên tác giả */
		case NXB: updateNxb(book); break;				/* Cập nhật nhà xuất bản */
		case CATEGORY: updateCategory(book); break;		/* Cập nhật thể loại */
		case YEAR: updateNamXB(book); break;			/* Cập nhật năm xuất bản */
		case QUANTITY: updateSoLuong(book); break;		/* Cập nhật số lượng sách */
		case IMPORT_PRICE: updateGiaNhap(book); break;	/* Cập nhật giá nhập vào */
		case SELL_PRICE: updateGiaBan(book); break;		/* Cập nhật giá bán */
		case 0: back = true; break;						/* Trở về menu quản lý sách */
		default:
			cout << "Lựa chọn không hợp lệ" << endl;
			break;
		}

		if (back == true)
		{
			/* Lưu thông tin xuốn csv trước khi back */
			BookManagement::storeToCsv();
			break;
		}
	}
}