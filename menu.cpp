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
	cout << setw(20) << setfill('=') << "" << endl;
	cout << "Quản lý khách hàng" << endl;
	cout << setw(20) << setfill('=') << "" << endl;
	cout << "1. Xem danh sách khách hàng" << endl;
	cout << "2. Thêm khách hàng mới" << endl;
	cout << "3. Chỉnh sửa thông tin khách hàng" << endl;
	cout << "4. Xóa thông tin khách hàng" << endl;
	cout << "5. TÌm kiếm khách hàng theo số điện thoại" << endl;
	cout << "6. Tìm kiếm khách hàng theo họ tên" << endl;
	cout << "0. Thoát" << endl;
	cout << setw(20) << setfill('=') << "" << endl;
}

/* Menu chức năng quản lý sách */
void BookMenu()
{
	cout << setw(20) << setfill('=') << "" << endl;
	cout << "Quản lý sách" << endl;
	cout << setw(20) << setfill('=') << "" << endl;
	cout << "1. Xem danh sách các loại sách trong kho" << endl;
	cout << "2. Thêm sách mới" << endl;
	cout << "3. Chỉnh sửa thông tin sách" << endl;
	cout << "4. Xóa thông tin sách" << endl;
	cout << "5. TÌm kiếm khách hàng theo ISBN" << endl;
	cout << "6. Tìm kiếm khách hàng theo tên sách" << endl;
	cout << "0. Thoát" << endl;
	cout << setw(20) << setfill('=') << "" << endl;
}