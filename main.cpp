#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <Windows.h>
#include <iomanip>
#include <ctime>
#include <vector>
#include "menu.h"
#include "KhachHang.h"
#include "users.h"

#include "userRegister.h"

using namespace std;

int main()
{
	/* Set up ban đầu để chương trình có thể hiểu và in ra ký tự Unicode */
	/* Note: hiện mặc định hỗ trợ hệ điều hành Window */
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);

	/* Mở main menu */
	//MainMenu();

	//KhachHang* kh = new KhachHang();

	//kh->XuatThongTin();
	UserManagement& Users = UserManagement::getInstance();

	userMain();
	
	/* Xuất thông tin khách hàng */
	vector<KhachHang*> danhSachKH = Users.getDanhSach();

	for (KhachHang* kh : danhSachKH)
	{
		kh->XuatThongTin();
	}
	
	return 0;
}