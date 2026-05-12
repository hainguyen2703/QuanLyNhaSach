#include <iostream>
#include <fstream>
#include <vector>
#include "UserManagement.h"
#include "loadData.h"
#include "global.h"

using namespace std;

/* Static function prototype */
static int getFileSizeInByte(ifstream& fileInput);

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
	char* line_c = new char[size];
	inputFile.getline(line_c, size);

	/* Chuyển sang dạng string */
	string line = line_c;
	delete[] line_c;

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