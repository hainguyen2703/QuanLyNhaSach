#include <iostream>
#include <vector>
#include <iomanip>
#include "CustomerManagement.h"
#include "common.h"

using namespace std;

/* Hàm truy cập instance duy nhất */
CustomerManagement& CustomerManagement::getInstance() {
    static CustomerManagement instance; // tạo 1 lần duy nhất
    return instance;
}

/* Hàm thêm một khách hàng mới */
void CustomerManagement::themKhachHang(KhachHang* kh) {
    this->danhSach.push_back(kh);
}

/* Hàm lấy danh sách khách hàng */
vector<KhachHang*>& CustomerManagement::getDanhSach() {
    return this->danhSach;
}

/* Lấy số lượng active account */
int CustomerManagement::getSoLuongKH()
{
    return this->danhSach.size();
}

/* Menu quản lý khách hàng */
void CustomerManagement::Menu()
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

/* Hàm tạo Khách Hàng mới */
void CustomerManagement::addCustomer()
{
    /* Tạo Khách Hàng mới */
    KhachHang* newCustomer = KhachHang::createNewKhachHang();

    /* Kiểm tra nếu Khách Hàng mới tạo thành công */
    if (newCustomer != NULL)
    {
        this->danhSach.push_back(newCustomer);	/* Thêm sách vào vector danhSach */
        cout << "Đã thêm tài khoản mới thành công!" << endl;
    }
}


/* Hàm xuất danh sách khách hàng trong hệ thống */
void CustomerManagement::XuatDanhSachKH()
{
    /* Tạo khung */
    cout << setfill('=')
        << setw(70) << "" << endl
        << setfill(' ') << setw(24) << "" << "Danh sách khách hàng" << endl
        << setfill('=') << setw(70) << "" << endl;
    cout << left << setfill(' ') 
        << setw(15) << "ID"
        << setw(15) << "|Class"
        << setw(15) << "|Phone"
        << "|Tên khách hàng" << endl;
	cout << setfill('=') << setw(70) << "" << endl;

    /* Xuất thông tin của khách hàng */
    for (KhachHang* kh : this->danhSach)
    { 
        cout << left << setfill(' ')
            << setw(15) << kh->getID()
            << "|" << setw(14) << kh->getLoaiThe()
            << "|" << setw(14) << kh->getPhone()
            << "|" << kh->getName() << endl;
        cout << setfill('_') << setw(70) << "" << endl;
    }
}

/* Hàm tìm kiếm theo số điện thoại */
int CustomerManagement::findPhone(const string& phone)
{
    for (int index = 0; index < this->danhSach.size(); index++)
    {
        if (danhSach[index]->getPhone() == phone)
        {
            /* Tìm thấy, trả về index */
            return index;
        }
    }

    /* Không tìm thấy, trả về -1 */
    return -1;
}

/* Hàm tìm kiếm theo mail */
int CustomerManagement::findMail(const string& mail)
{
    for (int index = 0; index < this->danhSach.size(); index++)
    {
        if (danhSach[index]->getMail() == mail)
        {
            /* Tìm thấy, trả về index */
            return index;
        }
    }

    /* Không tìm thấy, trả về -1 */
    return -1;
}

/* Hàm tìm kiếm theo tên */
int CustomerManagement::findName(const string& name)
{
    for (int index = 0; index < this->danhSach.size(); index++)
    {
        /* Đổi tên thành lowercase */
        string tmp = toLowerUtf8(danhSach[index]->getName());
        /* So sánh tên */
        if (tmp == name)
        {
            /* Tìm thấy, trả về index */
            return index;
        }
    }

    /* Không tìm thấy, trả về -1 */
    return -1;
}

/* Hàm tìm kiếm theo ID */
int CustomerManagement::findID(const string& id)
{
    for (int index = 0; index < this->danhSach.size(); index++)
    {
        /* So sánh ignore case */
        if (danhSach[index]->getID() == id)
        {
            /* Tìm thấy, trả về index */
            return index;
        }
    }

    /* Không tìm thấy, trả về -1 */
    return -1;
}

/* Hàm xóa khách hàng theo ID */
void CustomerManagement::XoaKhachHang(const int& index)
{
    /* Vì index luôn luôn hợp lệ nên không cần kiểm tra lại */
    /* Lấy địa chỉ của object cần xóa */
    KhachHang* kh = this->danhSach[index];
    
    /* Cập nhật vector */
    this->danhSach.erase(this->danhSach.begin() + index);

    /* Giải phóng bộ nhớ */
    delete kh;
}

/* Hàm load Khách Hàng từ csv file */
void CustomerManagement::loadFromCsv(const string& filename)
{
    /* Lấy Users object */
    CustomerManagement& Users = CustomerManagement::getInstance();

    /* Mở file */
    ifstream inputFile;
    inputFile.open(filename, ios::in);

    /* Kiểm tra nếu mở không được file */
    if (inputFile.is_open() != true)
    {
        cout << "Không tìm thấy file " << filename << endl;
        return;
    }

    /* Lấy file size */
    int size = getFileSizeInByte(inputFile);

    /* Mở được file => Lấy data */
    string line;
    bool bomChecked = false;
    while (getline(inputFile, line))
    {
        /* Xóa BOM ở line đầu tiên trong file */
        if (!bomChecked)
        {
            line.erase(line.begin(), line.begin() + 3);	/* Xóa BOM nếu có */
            bomChecked = true;
        }

        KhachHang* kh = loadUserFromCsvString(line);

        /* Thêm khách hàng vào vector */
        if (kh != nullptr)
        {
            Users.themKhachHang(kh);
        }
    }

    /* Lấy Cusomter ID mới nhất dùng cho việc tạo Customer mới sau này */
    string latestID = Users.getDanhSach()[Users.getDanhSach().size() - 1]->getID();
    /* Tách bỏ KH */
    KhachHang::setCntCustomerID(stoi(latestID.substr(2)));

    /* Đóng file */
    inputFile.close();
}

/* Hàm store Khách Hàng từ csv file */
void CustomerManagement::storeToCsv(const string& filename)
{
    /* Mở file cần lưu */
    ofstream outputFile;
    outputFile.open(filename, ios::binary | ios::out);

    /* Kiểm tra nếu mở file thất bại */
    if (outputFile.is_open() != true)
    {
        cout << "Không thể mở được file " << filename << endl;
        cout << "Lưu data thất bại" << endl;
        return;
    }

    /* Ghi BOM để file excel hiển thị Unicode */
    unsigned char bom[] = { 0xEF, 0xBB, 0xBF };
    outputFile.write((char*)bom, 3);

    /* Lấy danh sách khách hàng */
    vector<KhachHang*> danhSach = CustomerManagement::getInstance().getDanhSach();

    /* Ghi thông tin khách hàng vào file csv */
    for (KhachHang* kh : danhSach)
    {
        outputFile << kh->getCsvString() << "\n";
    }

    /* Đóng file */
    outputFile.close();
}