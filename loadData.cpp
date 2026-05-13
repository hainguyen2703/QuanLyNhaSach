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
static KhachHang* CollectCustomerData(string& line);

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
	while (getline(inputFile, line))
	{
		KhachHang* kh = CollectCustomerData(line);

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
	/* Lấy vị trí đầu file */
	fileInput.seekg(0, ios::end);

	/* Lấy vị trí cuối file */
	int fileSize = fileInput.tellg();

	/* Trả về đầu file */
	fileInput.seekg(0, ios::beg);

	return fileSize;
}

/* Hàm tách string thành customer data */
KhachHang* CollectCustomerData(string& line)
{
	vector<string> attribute;

	stringstream ss(line);
	string info;

	/* Tách dòng string theo delmi là dấu phẩy */
	while (getline(ss, info, ',')) {
		attribute.push_back(info);
	}

	int type = (attribute[6] == "1") ? 1 : 0;
	Date date = getDateFromString(attribute[5]);

	KhachHang* kh = new KhachHang(attribute[1], attribute[2], attribute[3], attribute[4], type);

	kh->setID(attribute[0]);
	kh->setDate(date);

	return kh;
}