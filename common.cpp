#include <iostream>
#include <algorithm>
#include <cctype>
#include <fstream>
#include <sstream>
#include <vector>
#include "common.h"
#include "CustomerManagement.h"

#ifndef NOMINMAX
#define NOMINMAX
#endif
#include "Windows.h"

using namespace std;

/* Thứ tự: ISBN, name, author, nxb, year, category, importPrice, sellingPrice, soLuong */
enum {
	ISBN = 0,
	NAME,
	AUTHOR,
	NXB,
	YEAR,
	CATEGORY,
	IMPORT_PRICE,
	SELLING_PRICE,
	SO_LUONG
};

static int utf8_length(const std::string& s);

/* Kiểm tra string input toàn space, tab hoặc newline hoặc empty */
bool isAllBlank(const string str)
{
	return str.find_first_not_of(" \t\n\r") == string::npos;
}

/* Clear input cache */
void clearInputCache()
{
	/* Clear input cache */
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

/* Hàm lấy 1 line input dạng string */
bool getStringLine(string& str)
{
	getline(cin, str);
	if (isAllBlank(str))
	{
		cout << "Input không hợp lệ" << endl;
		return false;
	}

	return true;
}

/* Hàm lấy lựa chọn chức năng muốn sử dụng 
 * Nếu input không hợp lệ: trả về -1 */
int getOption()
{
	int opt;
	/* Lấy giá trị input */
	cin >> opt;
	/* Kiểm tra input có phải giá trị digit không */
	if (cin.fail() == true)
	{
		/* Input không phải số nguyên */
		cin.clear();	/* Xóa lỗi */
		opt = -1;		/* Trả về - 1*/
	}

	/* Clear input cache */
	clearInputCache();

	return opt;
}

/* Hàm lấy giá trị chữ số */
int getNumber()
{
	int x;
	cin >> x;
	if (cin.fail()) 
	{
		cin.clear();              // xóa trạng thái lỗi
		cin.ignore(1000, '\n');   // bỏ ký tự sai trong buffer
		cout << "Nhập sai, vui lòng nhập chữ số\n";
		x = -1;
	}

	/* Clear input cache */
	clearInputCache();

	return x;

}

/* Kiểm tra string input có chứa ký tự không */
bool isAllDigit(const string& str)
{
	/* Kiểm tra nếu input chứa ký tự khác chữ số */
	for (char c : str)
	{
		if (isdigit(c) == false)
		{
			return false;
		}
	}

	return true;
}

/* Hàm convert string về uppercase */
string toUpper(const string& str)
{
	string result = str;
	transform(result.begin(), result.end(), result.begin(), [](unsigned char c) { return std::toupper(c); });
	return result;
}

/* Hàm convert string về lowercase */
string toLower(const string& str)
{
	string result = str;
	transform(result.begin(), result.end(), result.begin(), [](unsigned char c) { return std::tolower(c); });
	return result;
}

/* Hàm convert to lower case cho UTF-8 */
string toLowerUtf8(const string& str) {
	// UTF-8 → UTF-16
	int len = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, nullptr, 0);
	wstring wstr(len, 0);
	MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, &wstr[0], len);

	// tolower Unicode
	CharLowerBuffW(&wstr[0], wstr.size());

	// UTF-16 → UTF-8
	int outLen = WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, nullptr, 0, nullptr, nullptr);
	string out(outLen, 0);
	WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, &out[0], outLen, nullptr, nullptr);

	return out;
}

/* Hàm đếm số byte của chuỗi unicode */
int utf8_length(const string& s) {
	int len = 0;
	for (size_t i = 0; i < s.size(); ) {
		unsigned char c = s[i];
		if (c < 0x80) i += 1;      // 1 byte
		else if (c < 0xE0) i += 2;      // 2 byte
		else if (c < 0xF0) i += 3;      // 3 byte
		else               i += 4;      // 4 byte
		len++;
	}
	return len;
}

/* Hàm canh trái của chuỗi unicode */
void print_utf8_left(const string& s, int width) {
	int len = utf8_length(s);
	int pad = width - len;
	cout << s;
	for (int i = 0; i < pad; i++) cout << ' ';
}

/* Lấy size của file cần đọc */
int getFileSizeInByte(ifstream& fileInput)
{
	/* Di chuyển con trỏ file về cuối file */
	fileInput.seekg(0, ios::end);

	/* Lấy vị trí cuối file */
	int fileSize = fileInput.tellg();

	/* Trả về đầu file */
	fileInput.seekg(0, ios::beg);

	return fileSize;
}

/* Hàm tách string thành book data */
Book* loadBookFromCsvString(string& line)
{
	vector<string> attribute;

	stringstream ss(line);
	string info;
	int item_cnt = 0;

	/* Tách dòng string theo delmi là dấu gạch dọc */
	/* Thứ tự: ISBN, name, author, nxb, year, category, importPrice, sellingPrice, soLuong */
	while (getline(ss, info, '|'))
	{
		attribute.push_back(info);
	}

	/* Convert string sang double */
	double importPrice = stod(attribute[IMPORT_PRICE]);
	double sellingPrice = stod(attribute[SELLING_PRICE]);
	int soLuong = stoi(attribute[SO_LUONG]);

	/* Tạo khách hàng */
	return new Book(attribute[ISBN], attribute[NAME], attribute[AUTHOR], attribute[NXB], stoi(attribute[YEAR]), attribute[CATEGORY], importPrice, sellingPrice, stoi(attribute[SO_LUONG]));
}

/* Hàm tách string thành Khách Hàng data */
KhachHang* loadUserFromCsvString(string& line)
{
	vector<string> attribute;

	stringstream ss(line);
	string info;
	int item_cnt = 0;

	/* Tách dòng string theo delmi là dấu phẩy */
	while (getline(ss, info, '|'))
	{
		attribute.push_back(info);
	}

	/* Convert type sang int */
	int type = (attribute[6] == "1") ? 1 : 0;

	/* Convert string sang Date */
	Date date = getDateFromString(attribute[5]);

	/* Tạo khách hàng */
	KhachHang* kh = new KhachHang(attribute[1], attribute[2], attribute[3], attribute[4], type);

	/* Set thông tin ID và ngày đăng ký */
	kh->setID(attribute[0]);
	kh->setRegisterDate(date);

	/* Trả về con trỏ khách hàng */
	return kh;
}
