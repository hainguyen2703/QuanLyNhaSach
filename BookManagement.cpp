#include <fstream>
#include "book_ultis.h"
#include "BookManagement.h"
#include "common.h"

using namespace std;

/* Hàm truy cập instance duy nhất */
BookManagement& BookManagement::getInstance()
{
	static BookManagement instance;
	return instance;
}

/* Lấy danh sách Sách */
vector<Book*>& BookManagement::getDanhSachBooks()
{
	return this->books;
}

/* Menu quản lý sách */
void BookManagement::Menu()
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

/* Thêm sách mới */
void BookManagement::addBook()
{
	/* Tạo sách mới */
	Book* newBook = Book::createNewBook();

	/* Kiểm tra nếu sách mới tạo thành công */
	if (newBook != NULL)
	{
		this->books.push_back(newBook);	/* Thêm sách vào vector books */
		cout << "Đã thêm sách mới thành công!" << endl;

		/* Lưu xuống file csv ngay */
		BookManagement::storeToCsv();
	}
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

/* Hàm tìm kiếm theo ISBN */
int BookManagement::findISBN(const string& isbn)
{
	for (int i = 0; i < this->books.size(); i++)
	{
		if (books[i]->getIsbn() == isbn)
			return i;
	}
	/* Không tìm thấy */
	return -1;
}

/* Hàm tìm kiếm theo tên sách */
int BookManagement::findName(const std::string& name)
{
	for (int index = 0; index < this->books.size(); index++)
	{
		/* Đổi tên sách sang lowercase */
		string name_lwc = toLowerUtf8(this->books[index]->getName());

		/* So sánh */
		if (name_lwc == name)
			return index;
	}

	/* Không tìm thấy */
	return -1;
}

/* Remove book */
void BookManagement::removeBook(const int& index)
{
	vector<Book*> books = BookManagement::getInstance().getDanhSachBooks();

	/* Remove sách */
	Book* book = books[index];
	books.erase(books.begin() + index);
	delete book;

	/* Lưu xuống file csv ngay */
	BookManagement::storeToCsv();
}

/* Hàm store data */
void BookManagement::storeToCsv(const string& filename)
{
	/* Mở file để lưu */
	ofstream outputFile;
	outputFile.open(filename, ios::out);

	/* Kiểm tra nếu mở file thành công */
	if (outputFile.is_open() != true)
	{
		cout << "Không thể mở được file " << filename << endl;
		cout << "Lưu thông tin sách thất bại!!" << endl;
		return;
	}

	/* Ghi BOM để file excel hiển thị Unicode */
	unsigned char bom[] = { 0xEF, 0xBB, 0xBF };
	outputFile.write((char*)bom, 3);

	/* Ghi dữ liệu sách xuống file csv */
	BookManagement &Books = BookManagement::getInstance();
	vector<Book*>& danhSachBooks = Books.getDanhSachBooks();

	for (Book* book : danhSachBooks)
	{
		outputFile << book->getCsvString() << "\n";
	}

	/* Đóng file */
	outputFile.close();
}

/* Hàm load data */
void BookManagement::loadFromCsv(const std::string& filename)
{
	ifstream inputFile;
	inputFile.open(filename, ios::in);

	/* Kiểm tra nếu mở file thành công */
	if (inputFile.is_open() != true)
	{
		cout << "Không mở được file " << filename << endl;
	}

	/* Lấy file size */
	int size = getFileSizeInByte(inputFile);

	/* Mở được file => Lấy data */
	string line;
	bool bomChecked = false;
	BookManagement &books = BookManagement::getInstance();
	while (getline(inputFile, line))
	{
		/* Xóa BOM ở line đầu tiên trong file */
		if (!bomChecked)
		{
			line.erase(line.begin(), line.begin() + 3);	/* Xóa BOM nếu có */
			bomChecked = true;
		}

		/* Load book data */
		Book* book = loadBookFromCsvString(line);

		/* Thêm book vào vector */
		if (book != NULL)
		{
			books.getDanhSachBooks().push_back(book);
		}
	}

	/* Đóng file */
	inputFile.close();
}