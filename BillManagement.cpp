#include <iostream>
#include <string>
#include <fstream>
#include "main.h"
#include "customer_ultis.h"
#include "book_ultis.h"

using namespace std;

/* Hàm lấy instance của BillManagement */
BillManagement& BillManagement::getInstance()
{
	static BillManagement instance;
	return instance;
}

/* Hàm lấy list hóa đơn */
vector<HoaDon*>& BillManagement::getListHD()
{
	return this->listHoaDon;
}

void BillManagement::taoHoaDon()
{
	/* Lấy mã khách hàng */
	cout << "Nhập vào mã khách hàng: ";
	string maKH;
	if (getStringLine(maKH) != true)
		return;

	if (ktUserID(maKH) != true)
	{
		cout << "Input không hợp lệ" << endl;
		return;
	}

	/* Chuyển maKH về uppercase */
	maKH = toUpper(maKH);

	/* Kiểm tra nếu lấy được thông tin khách hàng */
	if (CustomerManagement::getInstance().findID(maKH) == -1)
	{
		cout << "Không tìm thấy khách hàng có mã " << maKH << endl;
		return;
	}

	/* Lấy ngày lập hóa đơn */
	Date date;
	cout << "Ngày xuất hóa đơn: ";
	cin >> date;

	/* Kiểm tra input */
	if (!cin)
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Ngày không hợp lệ" << endl;
		return;
	}
	else
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

	/* Kiểm tra ngày */
	if (validateDate(date) != true)
	{
		cout << "Ngày không hợp lệ" << endl;
		return;
	}

	/* Tạo hóa đơn chưa có item */
	HoaDon* hd = new HoaDon(maKH, date);

	/* Thêm item vào hóa đơn */
	/* Show list book hiện tại trong nhà sách */
	BookManagement::getInstance().XuatDanhSachBooks();

	bool exit = false;
	/* Loop nhập sách - số lượng */
	while (true)
	{
		cout << "Nhập mã isbn (hoặc nhập Q để dừng): ";
		string isbn;
		if (getStringLine(isbn) != true)
				continue;

		/* Kiểm tra exit */
		if (isbn == "Q" || isbn == "q")
			break;

		/* Kiểm tra input */
		if (isbnValidate(isbn) != true || BookManagement::getInstance().findISBN(isbn) == -1)
		{
			cout << "Input không hợp lệ" << endl;
			continue;
		}

		/* Lấy book */
		int remain = BookManagement::getInstance().getBookByIsbn(isbn)->getSoLuong();
		bool exit = false;
		cout << "Nhập vào số lượng: ";
		int soLuong;
		while (true)
		{
			cin >> soLuong;
			if (cin.fail())
			{
				cin.clear();              // xóa trạng thái lỗi
				cin.ignore(1000, '\n');   // bỏ ký tự sai trong buffer
				cout << "Nhập sai, vui lòng nhập chữ số: ";
				continue;
			}

			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			/* Kiểm tra nếu input âm */
			if (soLuong <= 0)
			{
				exit = true;
				break; /* Thoát inner while loop */
			}
			/* Kiểm tra nếu số lượng trong kho không đủ */
			else if (soLuong > remain)
			{
				cout << "Không đủ sách trong kho, số sách còn lại: " << remain << endl;
				break;
			}
			else
			{
				/* Add item vào hóa đơn */
				hd->addItem({ isbn, soLuong });
				break;
			}
		}

		if (exit == true) break; /* Dừng chọn isbn - số lượng */
	}

	/* Set hóa đơn nếu được */
	if (hd->setMaHD() != true)
	{
		delete hd;
	}
	else
	{
		/* In hóa đơn */
		hd->xuatHoaDon();
		/* Xác nhận */
		cout << "Xác nhận hóa đơn (Y/N): ";
		char ack;
		cin >> ack;

		/* Làm sạch buffer */
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		/* Kiểm tra nếu xác nhận tạo hóa đơn */
		if (ack == 'Y' || ack == 'y')
		{
			HoaDon::increaseMaHD();	//Tăng số lượng ID hóa đơn

			/* Add Hóa đơn vào list hóa đơn */
			this->listHoaDon.push_back(hd);
			/* Cập nhật Books trong thư viện sau khi tạo hóa đơn */
			for (Item item : hd->getListItems())
			{
				/* Thay đổi số lượng sách của isbn tương ứng trong kho */
				int sl = -1 * item.soLuong;
				BookManagement::getInstance().getBookByIsbn(item.isbn)->setSoLuong(sl, CAP_NHAT);
			}

			/* Lưu xuống file csv ngay */
			BookManagement::storeToCsv();	//Lưu sách
			BillManagement::storeToCsv();	//Lưu hóa đơn
			cout << "Đã lưu hóa đơn!!!" << endl;
		}
		else
		{
			/* Không tạo hóa đơn */
			delete hd;	//Xóa hóa đơn nháp vừa tạo
		}
	}
}

/* Hàm load data hóa đơn từ csv */
void BillManagement::loadFromCsv(const string& filename)
{
	/* Mở file */
	ifstream inputFile(filename, ios::in);

	/* Kiểm tra file mở được không */
	if (inputFile.is_open() != true)
	{
		cout << "Không thể mở được file " << filename << endl;
		return;
	}

	/* Lấy file size */
	int size = getFileSizeInByte(inputFile);

	string line;
	BillManagement& bm = BillManagement::getInstance();

	while (getline(inputFile, line))
	{
		HoaDon* hd = loadHoaDonFromCsvString(line);

		if (hd != NULL)
		{
			bm.listHoaDon.push_back(hd);
		}
	}

	/* Lấy countMaHD */
	string latestID = bm.listHoaDon[bm.listHoaDon.size() - 1]->getMaHD();
	HoaDon::setCountMaHD(stoi(latestID.substr(2)));

	/* Đóng file */
	inputFile.close();
}

/* Hàm store data hóa đơn xuống csv */
void BillManagement::storeToCsv(const string& filename)  
{
	ofstream outputFile(filename, ios::out);
	/* Kiểm tra file có mở được không */
	if (outputFile.is_open() != true)
	{
		cout << "Không thể mở được file " << filename << endl;
		cout << "Không thể lưu dữ liệu của hóa đơn" << endl;
		return;
	}

	/* Mở file thành công */
	/* Không cần lưu BOM vì hóa đơn không có unicode */
	for (const HoaDon* hd : BillManagement::getInstance().getListHD())
	{
		/* Lấy csv string */
		outputFile << hd->getCsvString() << "\n";
	}

	/* Đóng file */
	outputFile.close();
}