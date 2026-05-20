#include "Book.h"
#include "book_ultis.h"
#include "common.h"

using namespace std;

Book::Book(const string& isbn, const string& name, const string& author, const string& nxb, const int& year, const string& category, const double& importPrice, const double& sellingPrice, const int& soLuong)
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
	cin.ignore(100, '\n');	/* Làm sạch buffer */
	if (year <= 0)
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
	double importPrice;
	cout << "Giá nhập vào: ";
	cin >> importPrice;
	cin.ignore(100, '\n'); /* Làm sạch buffer */
	/* Mặc định giá nhập phải từ 10.000 vnd */
	if (importPrice < 10000)
	{
		cout << "Giá nhập không hợp lệ!!\n";
		return NULL;
	}

	double sellingPrice = importPrice * 1.3; /* Giá bán mặc định cao hơn 30% */

	/* 8. Số lượng */
	int soLuong;
	cout << "Số lượng: ";
	cin >> soLuong;
	cin.ignore(100, '\n'); /* Làm sạch buffer */
	if (soLuong <= 0)
	{
		cout << "Số lượng không hợp lệ!!\n";
		return NULL;
	}

	/* Tạo book mới dựa trên thông tin thu thập được */
	return new Book(isbn, name, author, nxb, year, category, importPrice, sellingPrice, soLuong);
}

/* Getter functions */
string Book::getIsbn()
{
	return this->isbn;
}

string Book::getName() const
{
	return this->name;
}

string Book::getAuthor() const
{
	return this->author;
}

string Book::getNxb() const
{
	return this->nxb;
}

int Book::getYear() const
{
	return this->year;
}

string Book::getCategory() const
{
	return this->category;
}

double Book::getImportPrice() const
{
	return this->importPrice;
}

double Book::getSellingPrice() const
{
	return this->sellingPrice;
}

int Book::getSoLuong() const
{
	return this->soLuong;
}

/* Setter function */
void Book::setIsbn(const string& isbn)
{
	this->isbn = isbn;
}

void Book::setName(const string& name)
{
	this->name = name;
}

void Book::setAuthor(const string& author)
{
	this->author = author;
}

void Book::setNxb(const string& nxb)
{
	this->nxb = nxb;
}

void Book::setYear(const int& year)
{
	this->year = year;
}

void Book::setCategory(const std::string& category)
{
	this->category = category;
}

void Book::setImportPrice(const double& importPrice)
{
	this->importPrice = importPrice;
}

void Book::setSellingPrice(const double& sellingPrice)
{
	this->sellingPrice = sellingPrice;
}

/* Hàm xuất thông tin sách */
void Book::XuatThongTin() const
{
	cout << setfill('=')
		<< setw(42) << "" << endl
		<< setfill(' ') << setw(12) << "" << "Thông tin sách" << endl
		<< setfill('=') << setw(42) << "" << endl;
	print_utf8_left("ISBN", 15);
	cout << ": " << this->isbn << endl;
	print_utf8_left("Tên sách", 15);
	cout << ": " << this->name << endl;
	print_utf8_left("Tác giả", 15);
	cout << ": " << this->author << endl;
	print_utf8_left("NXB", 15);
	cout << ": " << this->nxb << endl;
	print_utf8_left("Năm xuất bản", 15);
	cout << ": " << this->year << endl;
	print_utf8_left("Thể loại", 15);
	cout << ": " << this->category << endl;
	print_utf8_left("Giá nhập", 15);
	cout << ": " << this->importPrice << endl;
	print_utf8_left("Giá bán", 15);
	cout << ": " << this->sellingPrice << endl;
	print_utf8_left("Số lượng", 15);
	cout << ": " << this->soLuong << endl;
	cout << setfill('=') << setw(42) << "" << endl;
}

string Book::getCsvString() const
{
	/* Thứ tự: ISBN, name, author, nxb, year, category, importPrice, sellingPrice, soLuong */
	return isbn + "|" + name + "|" + author + "|" + nxb + "|" + to_string(year) + "|" + category + "|" + to_string(importPrice) + "|" + to_string(sellingPrice) + "|" + to_string(soLuong);
}
