#include <iostream>
#include <algorithm>
#include <cctype>
#include "common.h"
using namespace std;

/* Kiểm tra string input toàn space, tab hoặc newline */
bool isAllBlank(const string str)
{
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