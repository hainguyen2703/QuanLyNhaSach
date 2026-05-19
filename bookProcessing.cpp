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
static bool isbnValidate(const string& isbn);
static bool checkGS1Prefix(const string& isbn);
static bool isbnDigitCheck(const string& isbn);
static bool isIsbnRegistered(const string& isbn);

/* Hàm main của việc quản lý sách */
void bookMain()
{
	/* Lấy object Books */
	BookManagement Books = BookManagement::getInstance();

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
			case MOD_BOOK_E: /* Chỉnh sửa thông tin sách */ break;
			case DEL_BOOK_E: /* Xóa sách */ break;
			case FIND_BOOK_ISBN: /* Tìm kiếm sách theo ISBN */ break;
			case FIND_BOOK_NAME: /* Tìm kiếm sách theo tên */ break;
			default:
				back = true;
				break;
		}

		/* Back về main menu*/
		if (back == true) break;
	}
}

/* Hàm thu thập thông tin sách */
Book* collectBookInfo()
{
	/* 1. ISBN */
	string isbn;
	cout << "ISBN: ";
	getline(cin, isbn);
	/* Kiểm tra isbn */
	if (isbnValidate(isbn) != true)
	{
		cout << "ISBN không hợp lệ!!\n";
		return NULL;
	}

	/* 2. Tên sách */
	string name;
	cout << "Tên sách: ";
	getline(cin, name);
	if (isAllBlank(name))
	{
		cout << "Tên sách không hợp lệ!!\n";
		return NULL;
	}
	
	/* 3. Tác giả */
	string author;
	cout << "Tác giả: ";
	getline(cin, author);
	if (isAllBlank(author))
	{
		cout << "Tác giả không hợp lệ!!\n";
		return NULL;
	}

	/* 4. Nhà xuất bản */
	string nxb;
	cout << "Nhà xuất bản: ";
	getline(cin, nxb);
	if (isAllBlank(nxb))
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
		cout << "Năm xuất bản không hợp lệ";
		return NULL;
	}

	/* 6. Thể loại */
	string category;
	cout << "Thể loại: ";
	getline(cin, category);
	if (isAllBlank(category))
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
	if(soLuong <= 0)
	{
		cout << "Số lượng không hợp lệ!!\n";
		return NULL;
	}

	/* Tạo book mới dựa trên thông tin thu thập được */
	Book* newBook = new Book(isbn, name, author, nxb, year, category, importPrice, sellingPrice, soLuong);

	return newBook;
}

/* Hàm kiểm tra isbn có hợp lệ hay không */
/* Điều kiện để 1 ISBN-13 hợp lệ:
 * - Độ dài phải là 13 ký tự
 * - Ký tự đầu tiên phải là 978 hoặc 979
 * - Các ký tự còn lại phải là số
 */
bool isbnValidate(const string& isbn)
{
	/* 1. Kiểm tra nếu isbn rỗng 
	 * 2. Kiểm tra nếu isbn có độ dài khác 13 
	 * 3. Kiểm tra nếu isbn chứa ký tự không phải số 
	 * 4. Kiểm tra 3 chữ số đầu tiên có phải GS1 prefix 
	 * 5. Kiểm tra digit num của isbn */
	if (isAllBlank(isbn) || isbn.length() != 13 || isAllDigit(isbn) != true ||
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

/* Hàm kiểm tra nếu ISBN đã được đăng ký trong hệ thông */
bool isIsbnRegistered(const string& isbn)
{
	for(Book* book: BookManagement::getInstance().getDanhSachBooks())
	{
		/* ISBN là digit nên không cần quan tâm upper hay lowercase */
		if (book->getIsbn() == isbn)
		{
			return true;
		}
	}
	return false;
}