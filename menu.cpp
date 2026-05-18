#include <iostream>
#include <string>
#include <iomanip>
#include "menu.h"

using namespace std;

/* Ham trinh chieu main menu */
void MainMenu()
{
	cout <<"==============================" << endl; 
	cout <<"|      Quản Lý Nhà Sách      |" << endl;
	cout <<"==============================" << endl;
	cout <<"1. Quản lý khách hàng" << endl;
	cout <<"2. Quản lý sách" << endl;
	cout <<"3. Quản lý hóa đơn bán hàng" << endl;
	cout <<"0. Exit" << endl;
	cout <<"==============================" << endl;
}

/* Menu chức năng quản lý Khách hàng */
void CustomerMenu()
{
	cout << setfill('=') 
	     << setw(42) << "" << endl
	     << setfill(' ') << setw(12) << "" << "Quản lý khách hàng" << endl
	     << setfill('=') << setw(42) << "" << endl
		 << "1. Xem danh sách khách hàng" << endl
		 << "2. Thêm khách hàng mới" << endl
		 << "3. Chỉnh sửa thông tin khách hàng" << endl
		 << "4. Xóa thông tin khách hàng" << endl
		 << "5. Tìm kiếm khách hàng theo số điện thoại" << endl
		 << "6. Tìm kiếm khách hàng theo họ tên" << endl
		 << "0. Thoát" << endl
		 << setw(42) << "" << endl;
}

/* Menu chức năng quản lý sách */
void BookMenu()
{
	cout << setfill('=')
		<< setw(42) << "" << endl
		<< setfill(' ') << setw(12) << "" << "Quản lý sách" << endl
		<< setfill('=') << setw(42) << "" << endl
	    << "1. Xem danh sách các loại sách trong kho" << endl
		<< "2. Thêm sách mới" << endl
		<< "3. Chỉnh sửa thông tin sách" << endl
		<< "4. Xóa thông tin sách" << endl
		<< "5. TÌm kiếm khách hàng theo ISBN" << endl
		<< "6. Tìm kiếm khách hàng theo tên sách" << endl
		<< "0. Thoát" << endl
		<< setw(42) << "" << endl;
}