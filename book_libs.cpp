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