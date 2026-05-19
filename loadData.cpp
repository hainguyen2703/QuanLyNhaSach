#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include "UserManagement.h"
#include "loadData.h"
#include "global.h"

using namespace std;

/* Static function prototype */
static int getFileSizeInByte(ifstream& fileInput);
static KhachHang* loadCustomerData(string& line);

/* Hàm load data từ file csv */
void loadData()
{
	/* Lấy Users object */
	UserManagement& Users = UserManagement::getInstance();

	/* Mở file */
	ifstream inputFile;
	inputFile.open("CustomerData.csv", ios::binary | ios::in);

	/* Kiểm tra nếu mở không được file */
	if (inputFile.is_open() != true)
	{
		cout << "Không tìm thấy file " << CustomerData << endl;
		return;
	}

	/* Lấy file size */
	int size = getFileSizeInByte(inputFile);

	/* Mở được file => Lấy data */
	string line;
	bool bomChecked = false;
	while (getline(inputFile, line))
	{
		/* Xóa BOM ở line đầu tiên trong file */
		if (!bomChecked)
		{
			line.erase(line.begin(), line.begin() + 3);	/* Xóa BOM nếu có */
			bomChecked = true;
		}

		KhachHang* kh = loadCustomerData(line);

		/* Thêm khách hàng vào vector */
		if (kh != nullptr)
		{
			Users.themKhachHang(kh);
		}
	}

	/* Đóng file */
	inputFile.close();
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

/* Hàm tách string thành customer data */
KhachHang* loadCustomerData(string& line)
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