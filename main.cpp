#include <iostream>
#include <Windows.h>
#include "menu.h"

using namespace std;

int main()
{
	/* Set up ban đầu để chương trình có thể hiểu và in ra ký tự Unicode */
	/* Note: hiện mặc định hỗ trợ hệ điều hành Window */
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);

	/* Mở main menu */
	ShowMenu();
	
	return 0;
}