#include <iostream>
#include <string>
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

/* Hàm lấy lựa chọn chức năng muốn sử dụng */
int getOption()
{
	int opt;

	cin >> opt;

	/* Clear input cache */
	clearInputCache();

	return opt;
}