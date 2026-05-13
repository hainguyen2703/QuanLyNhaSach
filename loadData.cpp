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
static KhachHang* TransferData(string& line);

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
		(void)TransferData(line);
	}	

	/* Đóng file */
	inputFile.close();
}

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

KhachHang* TransferData(string& line)
{
	string id, name, phone, mail, address, date, type;
	stringstream ss(line);
	string info;

	vector<string> attribute;

	while (getline(ss, info, ',')) {
		attribute.push_back(info);
	}

	for (string str : attribute)
	{
		cout << str << ",";
	}
	cout << endl;

	return nullptr;
}