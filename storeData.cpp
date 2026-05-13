#include <iostream>
#include <fstream>
#include <vector>
#include "UserManagement.h"
#include "storeData.h"

using namespace std;

/* Hàm lưu thông tin customer xuống file csv */
void storeCustomerData()
{
	cout << "Tiến hành lưu thông tin khách hàng..." << endl;

	/* Mở file cần lưu */
	ofstream outputFile;
	outputFile.open("CustomerData.csv", ios::binary | ios::out);

	/* Kiểm tra nếu mở file thất bại */
	if (outputFile.is_open() != true)
	{
		cout << "Không thể mở được file CustomerData.csv!!!" << endl;
		cout << "Lưu data thất bại" << endl;

		return;
	}

	/* Ghi BOM để file excel hiển thị Unicode */
	unsigned char bom[] = { 0xEF, 0xBB, 0xBF };
	outputFile.write((char*)bom, 3);

	/* Lấy Users */
	UserManagement &Users = UserManagement::getInstance();
	/* Lấy danh sách khách hàng */
	vector<KhachHang*> danhSach = Users.getDanhSach();

	/* Ghi thông tin khách hàng vào file csv */
	for (KhachHang* kh : danhSach)
	{
		outputFile << kh->getCsvString() << "\n";
	}

	/* Đóng file */
	outputFile.close();
}