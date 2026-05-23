#include <iostream>
#include <iomanip>
#include "main.h"

using namespace std;

/* Static function prototype */
static void menuThongKe();
static void thongKeDoanhThu();
static bool getNgaySaoKe(int& month, int& year);
static vector<HoaDon*> getSelectHD(const int& month, const int& year);
static void khungThongKeDoanhThu(const int& month);
static long long getDoanhThuNgay(const int& ngay, const vector<HoaDon*>& listHoaDon);

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
			case 4: thongKeDoanhThu();  break;	/* Tính doanh thu theo ngày/tháng */
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

void khungThongKeDoanhThu(const int& month)
{
	cout << setfill('=')
		<< setw(29) << "" << endl
		<< setfill(' ') << setw(5) << "" << "Doanh thu tháng " << month << endl
		<< setfill('=') << setw(29) << "" << endl;
	
	cout << "|";
	print_utf8_left("Ngày", 8);
	cout << "|";
	print_utf8_left("Doanh thu (vnd)", 18);
	cout << "|" << endl;
	cout << setfill('=') << setw(29) << "" << endl;
}
/* Hàm thống kê doanh thu từng ngày trong tháng và cả tháng */
void thongKeDoanhThu()
{
	/* 1. Chọn tháng/năm muốn xem doanh thu */
	Date date;
	if (getNgaySaoKe(date.month, date.year) != true)
		return;

	/* List chứa hóa đơn hợp lệ */
	vector<HoaDon*> listHoaDon = getSelectHD(date.month, date.year);

	/* In khung */
	khungThongKeDoanhThu(date.month);

	/* Lấy số ngày trong tháng */
	int day = getDayInMonth(date);

	long long doanhThuThang = 0;

	/* Xuất doanh thu */
	for (int i = 1; i <= day; i++)
	{
		/* Tính doanh thu ngày */
		long long doanhThuNgay = getDoanhThuNgay(i, listHoaDon);
		doanhThuThang += doanhThuNgay;

		/* In tổng doanh thu của ngày */
		string ngayIn = (i < 10) ? ("0" + to_string(i)) : to_string(i);
		ngayIn += "/";
		ngayIn += (date.month < 10) ? ("0" + to_string(date.month)) : (to_string(date.month));

		cout << "|" << right << setfill(' ')
			<< setw(8) << ngayIn << "|"
			<< setw(18) << doanhThuNgay << "|" << endl
			<< setfill('_') << setw(29) << "" << endl;
	}

	/* In tổng doanh thu của tháng */
	cout << "|";
	print_utf8_left("Tổng", 8);
	cout << "|" << right << setfill(' ') << setw(18) << doanhThuThang << "|" << endl;

	cout << setfill('=') << setw(29) << "" << endl;
}

/* Hàm lấy tháng và năm để xem doanh thu */
bool getNgaySaoKe(int& month, int& year)
{
	/* 1. Chọn tháng/năm muốn xem doanh thu */
	cout << "Xem doanh thu của tháng/năm: ";
	string date;
	if (getStringLine(date) != true)
		return false;

	/* Kiểm tra format */
	int pos = date.find_first_of("/");

	/* Kiểm tra nếu không đúng format */
	if (pos == string::npos)
	{
		cout << "Input không hợp lệ" << endl;
		return false;
	}

	/* Lấy tháng năm */
	month = stoi(date.substr(0, pos));
	year = stoi(date.substr(pos + 1));

	/* Kiểm tra tháng năm hợp lệ */
	if (month < 1 || month > 12)
	{
		cout << "Tháng không hợp lệ" << endl;
		return false;
	}
	else if (year < 0 || year > getCurrentDate().year)
	{
		cout << "Năm không hợp lệ" << endl;
		return false;
	}

	return true;
}

/* Hàm lấy các hóa đơn trong năm và tháng được chọn */
vector<HoaDon*> getSelectHD(const int& month, const int& year)
{
	vector<HoaDon*> listHoaDon;

	/* Duyệt qua các hóa đơn */
	for (HoaDon* hd : BillManagement::getInstance().getListHD())
	{
		/* Lấy ngày lập hóa đơn */
		Date date = hd->getDate();

		/* Kiểm tra năm và tháng hợp lệ */
		if (date.year == year && date.month == month)
		{
			/* Add hóa đơn vào list */
			listHoaDon.push_back(hd);
		}
	}

	return listHoaDon;
}

/* Hàm tính doanh thu theo ngày */
long long getDoanhThuNgay(const int& ngay, const vector<HoaDon*>& listHoaDon)
{
	long long sum = 0;
	for (HoaDon* hd : listHoaDon)
	{
		if (hd->getDate().day == ngay)
		{
			sum += hd->getTongTien();
		}
	}

	return sum;
}