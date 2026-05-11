#include <iostream>
#include <fstream>
#include "UserManagement.h"

void storeData(UserManagement& Users)
{
	cout << "Tiến hành lưu thông tin khách hàng..." << endl;

	/* Mở file cần lưu */
	ofstream outputFile;
	outputFile.open("CustomerData.txt", ios::binary);

}