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
		<< "5. TÌm kiếm theo ISBN" << endl
		<< "6. Tìm kiếm theo tên sách" << endl
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

/* Hàm lấy Book theo mã ISBN */
Book* BookManagement::getBookByIsbn(const string& isbn)
{
	return this->books[findISBN(isbn)];
}

/* Hàm xuất danh sách book */
void BookManagement::XuatDanhSachBooks() const
{
	/* Tạo khung */
	cout << setfill('=')
		<< setw(120) << "" << endl
		<< setfill(' ') << setw(40) << "" << "List thông tin sách" << endl
		<< setfill('=') << setw(120) << "" << endl;

	cout << left << setfill(' ')
		 << setw(3) << "No." << "|"
		 << setw(14) << "ISBN" << "|";
	print_utf8_left("Tên sách", 48);
	cout << "|";
	print_utf8_left("Tác giả", 30);
	cout << "|";
	print_utf8_left("Số lượng", 10);
	cout << "|Giá (vnd)" << endl;
	cout << setfill('=') << setw(120) << "" << endl;

	/* Xuất thông tin của sách */
	int cnt = 1;
	for (Book* book : this->books)
	{
		cout << left << setfill(' ')
			 << setw(3) << cnt++ << "|"
			 << setw(14) << book->getIsbn() << "|";
		print_utf8_left(book->getName(), 48);
		cout << "|";
		print_utf8_left(book->getAuthor(), 30);
		cout << left << setfill(' ')
			 << "|" << std::setw(10) << book->getSoLuong()
			 << "|" << book->getSellingPrice() << endl;
		cout << setfill('_') << setw(120) << "" << endl;
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
vector<Book*> BookManagement::findName(const string& name)
{
	/* Danh sách các book trùng tên (nếu có) */
	vector<Book*> list_book;

	string findName_lwc = toLowerUtf8(name);

	for (int index = 0; index < this->books.size(); index++)
	{
		/* Đổi tên sách sang lowercase */
		string name_lwc = toLowerUtf8(this->books[index]->getName());

		/* So sánh */
		if (name_lwc == findName_lwc)
		{
			list_book.push_back(this->books[index]);
		}
	}

	return list_book;
}

/* Remove book */
void BookManagement::removeBook(const int& index)
{
	/* Remove sách */
	Book* book = this->books[index];
	this->books.erase(this->books.begin() + index);
	delete book;

	/* Lưu xuống file csv ngay */
	BookManagement::storeToCsv();
}

/* Hàm thống kê tổng số sách */
int BookManagement::TongSoLuongSach()
{
	int sum = 0;
	for (Book* book : this->books)
	{
		sum += book->getSoLuong();
	}

	return sum;
}

/* Hàm lọc ra các thể loại sách trong kho */
vector<string> BookManagement::listCategory()
{
	vector<string> category;

	for (Book* book : this->books)
	{
		bool found = false;
		string bookType = toLowerUtf8(book->getCategory());

		/* Kiểm tra nếu category đã add vào rồi */
		for (string theloai : category)
		{
			if (theloai == bookType)
			{
				found = true;
				break;
			}
		}

		/* Nếu không tìm thấy thì add vào list */
		if (!found) category.push_back(bookType);
	}

	return category;
}

/* Hàm tính tổng số sách theo thể loại */
int BookManagement::soLuongTheoTheLoai(const std::string& category)
{
	int sum = 0;

	for (Book* book : this->books)
	{
		if (category == toLowerUtf8(book->getCategory()))
			sum += book->getSoLuong();
	}

	return sum;
}

/* Hàm thống kê sách theo thể loại */
void BookManagement::thongKeByCategory()
{
	/* Lấy danh sách các thể loại sách */
	vector<string> listCategory = this->listCategory();

	/* Tạo khung */
	cout << setfill('=')
		<< setw(42) << "" << endl
		<< setfill(' ') << setw(10) << "" << "Thống kê theo thể loại" << endl
		<< setfill('=') << setw(42) << "" << endl;

	print_utf8_left("Thể loại", 19);
	cout << "|" << "Số lượng (quyển)" << endl;
	cout << setfill('=') << setw(42) << "" << endl;

	for (string category : listCategory)
	{
		print_utf8_left(category, 20);
		cout << "|" << this->soLuongTheoTheLoai(category) << endl;
		cout << setfill('_') << setw(42) << "" << endl;
	}
	cout << setfill('=') << setw(42) << "" << endl;
}

/* Hàm thống kê sách đã hết hàng */
void BookManagement::listOutOfStock()
{
	/* Tạo khung */
	cout << setfill('=')
		<< setw(42) << "" << endl
		<< setfill(' ') << setw(12) << "" << "Sách đã hết hàng" << endl
		<< setfill('=') << setw(42) << "" << endl;
	cout << left << setfill(' ')
		<< setw(3) << "No."
		<< setw(15) << "|ISBN" << "|";
	print_utf8_left("Tên sách", 25);
	cout << endl << setfill('=') << setw(42) << "" << endl;

	int cnt = 1;
	for (Book* book : this->books)
	{
		/* Kiểm tra nếu số lượng sách = 0*/
		if (book->getSoLuong() == 0)
		{
			cout << left << setfill(' ')
				<< setw(3) << cnt++
				<< "|" << setw(14) << book->getIsbn() << "|";
			print_utf8_left(book->getName(), 25);
			cout << endl << setfill('_') << setw(42) << "" << endl;
		}
	}
	cout << setfill('=') << setw(42) << "" << endl;
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

	if (size == 0)
	{
		inputFile.close();
		return;
	}

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

		/* Kiểm tra nếu dòng đang đọc rỗng */
		if (line.empty()) continue;

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

/* Hàm hủy */
BookManagement::~BookManagement()
{
	for (Book* b : this->books)
	{
		delete b;
	}
}