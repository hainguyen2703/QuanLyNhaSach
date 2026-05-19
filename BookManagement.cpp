#include "book_ultis.h"
#include "BookManagement.h"
#include "common.h"

using namespace std;

/* Hàm truy cập instance duy nhất */
BookManagement BookManagement::getInstance()
{
	static BookManagement instance;
	return instance;
}

/* Lấy danh sách Sách */
vector<Book*>& BookManagement::getDanhSachBooks()
{
	return this->books;
}

/* Thêm sách mới */
void BookManagement::addBook()
{
	/* Tạo sách mới */
	Book* newBook = collectBookInfo();

	/* Kiểm tra nếu sách mới tạo thành công */
	if (newBook != NULL)
	{
		this->books.push_back(newBook);	/* Thêm sách vào vector books */
	}
}

/* Menu quản lý sách */
void BookManagement::bookMenu()
{
	cout << setfill('=')
		<< setw(42) << "" << endl
		<< setfill(' ') << setw(12) << "" << "Quản lý sách" << endl
		<< setfill('=') << setw(42) << "" << endl
		<< "1. Xem danh sách các loại sách trong kho" << endl
		<< "2. Thêm sách mới" << endl
		<< "3. Chỉnh sửa thông tin sách" << endl
		<< "4. Xóa thông tin sách" << endl
		<< "5. TÌm kiếm khách hàng theo ISBN" << endl
		<< "6. Tìm kiếm khách hàng theo tên sách" << endl
		<< "0. Thoát" << endl
		<< setw(42) << "" << endl;
}

/* Hàm xuất danh sách book */
void BookManagement::XuatDanhSachBooks() const
{
	/* Tạo khung */
	cout << setfill('=')
		<< setw(70) << "" << endl
		<< setfill(' ') << setw(24) << "" << "List thông tin sách" << endl
		<< setfill('=') << setw(70) << "" << endl;

	print_utf8_left("Tên sách", 48);
	cout << "|";
	print_utf8_left("Số lượng", 10);
	cout << "|Giá (vnd)" << endl;
	cout << setfill('=') << setw(70) << "" << endl;

	/* Xuất thông tin của sách */
	for (Book* book : this->books)
	{
		print_utf8_left(book->getName(), 48);
		cout << left << setfill(' ')
			 << "|" << std::setw(10) << book->getSoLuong()
			 << "|" << book->getSellingPrice() << endl;
		cout << setfill('_') << setw(70) << "" << endl;
	}
}
