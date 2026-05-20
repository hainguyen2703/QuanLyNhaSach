#include "book_ultis.h"

using namespace std;

/* Static function prototype */
static bool checkGS1Prefix(const string& isbn);
static bool isbnDigitCheck(const string& isbn);

/* Hàm kiểm tra isbn có hợp lệ hay không */
/* Điều kiện để 1 ISBN-13 hợp lệ:
 * Độ dài phải là 13 ký tự
 * Ký tự đầu tiên phải là 978 hoặc 979
 * Các ký tự còn lại phải là số
 */
bool isbnValidate(const string& isbn)
{
	/* 1. Kiểm tra nếu isbn có độ dài khác 13
	 * 2. Kiểm tra nếu isbn chứa ký tự không phải số
	 * 3. Kiểm tra 3 chữ số đầu tiên có phải GS1 prefix
	 * 4. Kiểm tra digit num của isbn */
	if (isbn.length() != 13 || isAllDigit(isbn) != true ||
		checkGS1Prefix(isbn) != true ||
		isbnDigitCheck(isbn) != true)
		return false;

	return true;
}

/* Hàm kiểm tra GS1 Prefix */
bool checkGS1Prefix(const string& isbn)
{
	vector<string> gs1_prefix = { "978", "979" };
	for (string gs1 : gs1_prefix)
	{
		if (isbn.substr(0, 3) == gs1)
		{
			return true;
		}
	}
	return false;
}

/* Hàm kiểm tra ISBN Digit check number */
bool isbnDigitCheck(const string& isbn)
{
	int sum = 0;
	int digitNum = 0;

	for (int i = 0; i < isbn.size() - 1; i++)
	{
		int digit = isbn[i] - '0'; /* Chuyển sang integer */
		/* Tính tổng isbn */
		sum += (i % 2 == 0) ? digit : (3 * digit);
	}

	digitNum = (10 - (sum % 10)) % 10;

	/* So sánh digit num tính được và digit num trong isbn */
	return (digitNum == (isbn[isbn.size() - 1] - '0')) ? true : false;
}

/* Menu chức năng edit thông tin khách hàng */
void editBookMenu()
{
	cout << setfill('=') << setw(42) << "" << endl
		<< setfill(' ') << setw(10) << "" << "Cập nhật thông tin" << endl
		<< setfill('=') << setw(42) << "" << endl
		<< "1. Cập nhật ISBN" << endl
		<< "2. Cập nhật tên sách" << endl
		<< "3. Cập nhật tác giả" << endl
		<< "4. Cập nhật nhà xuất bản" << endl
		<< "5. Cập nhật thể loại" << endl
		<< "6. Cập nhật năm xuất bản" << endl
		<< "7. Cập nhật số lượng" << endl
		<< "8. Cập nhật giá nhập" << endl
		<< "9. Cập nhật giá bán" << endl
		<< "0. Thoát" << endl
		<< setw(42) << "" << endl;
}

/* Cập nhật ISBN */
void updateISBN(const int& index)
{
	cout << "Nhập vào isbn mới: ";
	string isbn;
	if (getStringLine(isbn) != true || isbnValidate(isbn) != true)
	{
		cout << "ISBN không hợp lệ" << endl;
		return;
	}

	/* Cập nhật */
	BookManagement::getInstance().getDanhSachBooks()[index]->setIsbn(isbn);
	cout << "Cập nhật isbn thành công" << endl;
}

/* Cập nhật tên sách */
void updateBookName(Book* book)
{
	cout << "Nhập vào tên sách: ";
	string name;
	if(getStringLine(name) != true)
	{
		cout << "Tên sách không hợp lệ" << endl;
		return;
	}

	book->setName(name);
}

void updateAuthor(Book* book)
{
	cout << "Nhập vào tên tác giả: ";
	string author;
	if(getStringLine(author) != true)
	{
		cout << "Tên không hợp lệ" << endl;
		return;
	}

	book->setAuthor(author);
}

void updateNxb(Book* book)
{
	cout << "Nhập vào tên nxb: " << endl;
	string nxb;
	if (getStringLine(nxb) != true)
	{
		cout << "Tên không hợp lệ" << endl;
		return;
	}

	book->setNxb(nxb);
}