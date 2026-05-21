#include <iostream>
#include <iomanip>
#include "main.h"

using namespace std;

/* Static function prototype */
static void menuThongKe();

void mainThongKe()
{
	while (true)
	{
		/* Show menu */
		menuThongKe();
		cout << "Nhập vao thống kê muốn xem: ";
		int opt = getOption();

		BookManagement& bm = BookManagement::getInstance();
		CustomerManagement& cm = CustomerManagement::getInstance();

		switch (opt)
		{
			case 1: cout << "Tổng số lượng sách trong kho: " << bm.TongSoLuongSach() << " quyển" << endl; break;	/* Thống kê tổng số sách */
			case 2: bm.thongKeByCategory();  break;		/* Thống kê sách theo thể loại */
			case 3: cm.thongKeTheoThe(); break;			/* Thống kê khách hàng theo loại thẻ */
			case 4: break;	/* Tính doanh thu theo ngày/tháng */
			case 5: bm.listOutOfStock(); break;	/* Thống kê danh sách các sách đã hết hàng */
			case 0: break;	/* Trở về main */
			default:
				cout << "Lựa chọn không hợp lệ" << endl;
				break;
		}

		/* Trở về main menu */
		if (opt == 0) break;
	}
}

/* Menu thống kê */
void menuThongKe()
{
	cout << setfill('=')
		<< setw(42) << "" << endl
		<< setfill(' ') << setw(17) << "" << "Thống kê" << endl
		<< setfill('=') << setw(42) << "" << endl
		<< "1. Tổng số lượng sách hiện có trong kho" << endl
		<< "2. Số lượng sách theo thể loại" << endl
		<< "3. Số lượng khách hàng theo loại thẻ" << endl
		<< "4. Tính tổng số doanh thu theo ngày/tháng" << endl
		<< "5. Danh sách các sách đã hết hàng" << endl
		<< "0. Thoát" << endl
		<< setw(42) << "" << endl;
}