#include <iostream>
#include <algorithm>
#include <cctype>
#include "common.h"
#include "UserManagement.h"

#ifndef NOMINMAX
#define NOMINMAX
#endif
#include "Windows.h"

using namespace std;

static int utf8_length(const std::string& s);

/* Kiểm tra string input toàn space, tab hoặc newline hoặc empty */
bool isAllBlank(const string str)
{
	if (str.empty()) return true;

	/* Duyệt qua từng ký tự */
	for (char c : str)
	{
		/* Kiểm tra nếu ký tự khác blank */
		/* isspace return 0 nếu ký tự check khác space */
		if (isspace(c) == 0)
			return false;
	}

	/* Không tìm thấy ký tự nào khác -> All blank*/
	return true;
}

/* Clear input cache */
void clearInputCache()
{
	/* Clear input cache */
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
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

/* Kiểm tra xem User ID có hợp lệ hay không */
bool ktUserID(const string& id)
{
	/* Kiểm tra id empty hoặc size không đủ */
	if (id.empty() || id.size() != 10)
	{
		return false;
	}

	/* Kiểm tra ID có bắt đầu bằng KH */
	string tmp = toUpper(id);

	if (tmp.find_first_of("KH") != 0)
	{
		return false;
	}

	return true;
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

/* Hàm kiểm tra số điện thoại hợp lệ hay không */
bool phoneValidate(const string& phone)
{
	/* Kiểm tra phone input có đủ 10 chữ số */
	if (phone.size() != 10 || phone[0] != '0' || isAllDigit(phone) != true)
	{
		cout << "Số điện thoại không hợp lệ";
		return false;
	}

	/* Kiểm tra số điện thoại đã được đăng ký chưa */
	if (UserManagement::getInstance().findPhone(phone) != -1)
	{
		cout << "Số điện thoại đã được đăng ký!!!" << endl;
		return false;
	}

	return true;
}

/* Hàm kiểm tra mail input */
bool mailValidate(const string& mail)
{
	/* Mail không có @gmail.com và @gmail.com không phải là chuỗi kết thúc */
	if (mail.size() <= 10)
	{
		cout << "Địa chỉ mail không hợp lệ" << endl;
		return false;
	}

	string tmp = toLower(mail);
	if (tmp.rfind("@gmail.com") != (mail.size() - 10))
	{
		cout << "Địa chỉ mail không hợp lệ" << endl;
		return false;
	}

	/* Kiểm tra xem mail đã được đăng ký chưa */
	if (UserManagement::getInstance().findMail(tmp) != -1)
	{
		cout << "Địa chỉ mail đã được đăng ký!!!" << endl;
		return false;
	}

	/* Hợp lệ */
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
