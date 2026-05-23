#include "Book.h"
#include "book_ultis.h"
#include "common.h"

using namespace std;

Book::Book(const string& isbn, const string& name, const string& author, const string& nxb, const int& year, const string& category, const long long& importPrice, const long long& sellingPrice, const int& soLuong)
{
	this->isbn = isbn;
	this->name = name;
	this->author = author;
	this->nxb = nxb;
	this->year = year;
	this->category = category;
	this->importPrice = importPrice;
	this->sellingPrice = sellingPrice;
	this->soLuong = soLuong;
}

/* Hàm thuộc về class Book, dùng để collect thông tin và create book mới */
Book* Book::createNewBook()
{
	/* 1. ISBN */
	string isbn;
	cout << "ISBN: ";
	/* Kiểm tra isbn */
	if (getStringLine(isbn) != true || isbnValidate(isbn) != true)
	{
		cout << "ISBN không hợp lệ!!\n";
		return NULL;
	}

	/* Kiểm tra nếu ISBN đã tồn tại */
	if (BookManagement::getInstance().findISBN(isbn) != -1)
	{
		cout << "ISBN đã có trong hệ thống, xin đổi sang mục quản lý kho để cập nhật số lượng sách" << endl;
		return NULL;
	}

	/* 2. Tên sách */
	string name;
	cout << "Tên sách: ";
	if(getStringLine(name) != true)
	{
		cout << "Tên sách không hợp lệ!!\n";
		return NULL;
	}

	/* 3. Tác giả */
	string author;
	cout << "Tác giả: ";
	if(getStringLine(author) != true)
	{
		cout << "Tác giả không hợp lệ!!\n";
		return NULL;
	}

	/* 4. Nhà xuất bản */
	string nxb;
	cout << "Nhà xuất bản: ";
	if(getStringLine(nxb) != true)
	{
		cout << "Nhà xuất bản không hợp lệ!!\n";
		return NULL;
	}

	/* 5. Năm xuất bản */
	int year;
	cout << "Năm xuất bản: ";
	cin >> year;
	if (cin.fail())
	{
		cin.clear();              // xóa trạng thái lỗi
		cin.ignore(1000, '\n');   // bỏ ký tự sai trong buffer
		cout << "Năm xuất bản không hợp lệ" << endl;
		return NULL;
	}

	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	if (year <= 0 || year > getCurrentDate().year)
	{
		cout << "Năm xuất bản không hợp lệ" << endl;
		return NULL;
	}

	/* 6. Thể loại */
	string category;
	cout << "Thể loại: ";
	if(getStringLine(category) != true)
	{
		cout << "Thể loại không xác định\n";
		category = "NA";
	}

	/* 7. Giá nhập */
	long long importPrice;
	cout << "Giá nhập vào: ";
	cin >> importPrice;
	if (cin.fail())
	{
		cin.clear();              // xóa trạng thái lỗi
		cin.ignore(1000, '\n');   // bỏ ký tự sai trong buffer
		cout << "Giá nhập không hợp lệ!!!" << endl;
		return NULL;
	}

	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	/* Mặc định giá nhập phải từ 10.000 vnd */
	if (importPrice < 10000)
	{
		cout << "Giá nhập không hợp lệ!!\n";
		return NULL;
	}

	long long sellingPrice = importPrice * 1.3; /* Giá bán mặc định cao hơn 30% */

	/* 8. Số lượng */
	int soLuong;
	cout << "Số lượng: ";
	cin >> soLuong;
	if (cin.fail())
	{
		cin.clear();              // xóa trạng thái lỗi
		cin.ignore(1000, '\n');   // bỏ ký tự sai trong buffer
		cout << "Số lượng không hợp lệ!!" << endl;
		return NULL;
	}

	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	if (soLuong <= 0)
	{
		cout << "Số lượng không hợp lệ!!\n";
		return NULL;
	}

	/* Tạo book mới dựa trên thông tin thu thập được */
	return new Book(isbn, name, author, nxb, year, category, importPrice, sellingPrice, soLuong);
}

/***********************Getter functions***********************/
/* Hàm lấy isbn */
string Book::getIsbn()
{
	return this->isbn;
}

/* Hàm lấy tên sách */
string Book::getName() const
{
	return this->name;
}

/* Hàm lấy tác giả */
string Book::getAuthor() const
{
	return this->author;
}

/* Hàm lấy nxb */
string Book::getNxb() const
{
	return this->nxb;
}

/* Hàm lấy năm xuất bản */
int Book::getYear() const
{
	return this->year;
}

/* Hàm lấy thể loại */
string Book::getCategory() const
{
	return this->category;
}

/* Hàm lấy giá nhập */
long long Book::getImportPrice() const
{
	return this->importPrice;
}

/* Hàm lấy giá bán */
long long Book::getSellingPrice() const
{
	return this->sellingPrice;
}

/* Hàm lấy số lượng sách */
int Book::getSoLuong() const
{
	return this->soLuong;
}

/*********************** Setter functions ***********************/
/* Hàm set isbn */
void Book::setIsbn(const string& isbn)
{
	this->isbn = isbn;
}

/* Hàm set tên sách */
void Book::setName(const string& name)
{
	this->name = name;
}

/* Hàm set tác giả */
void Book::setAuthor(const string& author)
{
	this->author = author;
}

/* Hàm set nxb */
void Book::setNxb(const string& nxb)
{
	this->nxb = nxb;
}

/* Hàm set năm xuất bản */
void Book::setYear(const int& year)
{
	this->year = year;
}

/* Hàm set số lượng sách */
void Book::setSoLuong(const int& n, const int& type)
{
	/* Set gia trị thẳng */
	if (type == SET_GIA_TRI)
		this->soLuong = n;
	else
	{
		if (this->soLuong + n <= 0)
			this->soLuong = 0;
		else
			this->soLuong += n;
	}
}

/* Hàm set thể loại */
void Book::setCategory(const std::string& category)
{
	this->category = category;
}

/* Hàm set giá nhập sách*/
void Book::setImportPrice(const long long& importPrice)
{
	this->importPrice = importPrice;
}

/* Hàm set giá bán */
void Book::setSellingPrice(const long long& sellingPrice)
{
	this->sellingPrice = sellingPrice;
}

/* Hàm xuất thông tin sách */
void Book::XuatThongTin() const
{
	print_utf8_left(this->isbn, 15);
	cout << "|";
	print_utf8_left(this->name, 25);
	cout << "|";
	print_utf8_left(this->author, 20);
	cout << "|";
	print_utf8_left(this->nxb, 20);
	cout << "|";
	print_utf8_left(to_string(this->year), 10);
	cout << "|";
	print_utf8_left(this->category, 15);
	cout << "|";
	print_utf8_left(to_string(this->importPrice), 15);
	cout << "|";
	print_utf8_left(to_string(this->sellingPrice), 15);
	cout << "|";
	print_utf8_left(to_string(this->soLuong), 15);
}

/* Chuyển thành chuỗi đê lưu data ở csv */
string Book::getCsvString() const
{
	/* Thứ tự: ISBN, name, author, nxb, year, category, importPrice, sellingPrice, soLuong */
	return isbn + "|" + name + "|" + author + "|" + nxb + "|" + to_string(year) + "|" + category + "|" + to_string(importPrice) + "|" + to_string(sellingPrice) + "|" + to_string(soLuong);
}
