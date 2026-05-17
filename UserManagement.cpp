#include <iostream>
#include <vector>
#include <iomanip>
#include "UserManagement.h"

using namespace std;

/* Hàm truy cập instance duy nhất */
UserManagement& UserManagement::getInstance() {
    static UserManagement instance; // tạo 1 lần duy nhất
    return instance;
}

/* Hàm thêm một khách hàng mới */
void UserManagement::themKhachHang(KhachHang* kh) {
    this->danhSach.push_back(kh);
}

/* Hàm lấy danh sách khách hàng */
vector<KhachHang*>& UserManagement::getDanhSach() {
    return this->danhSach;
}

/* Lấy số lượng active account */
int UserManagement::getSoLuongKH()
{
    return this->danhSach.size();
}

/* Hàm xuất danh sách khách hàng trong hệ thống */
void UserManagement::XuatDanhSachKH()
{
    /* Tạo khung */
    cout << setfill('_') << setw(70) << "" << endl;
    cout << left << setfill(' ') 
        << setw(15) << "|ID"
        << setw(15) << "|Class"
        << setw(15) << "|Phone"
        << "|Tên khách hàng" << endl;
	cout << setfill('_') << setw(70) << "" << endl;

    /* Xuất thông tin của khách hàng */
    for (KhachHang* kh : this->danhSach)
    { 
        cout << left << setfill(' ')
            << "|" << setw(14) << kh->getID()
            << "|" << setw(14) << kh->getLoaiThe()
            << "|" << setw(14) << kh->getPhone()
            << "|" << kh->getName() << endl;
    }
    cout << setfill('_') << setw(70) << "" << endl;
}

/* Hàm tìm kiếm theo số điện thoại */
int UserManagement::findPhone(const string& phone)
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
int UserManagement::findMail(const string& mail)
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
int UserManagement::findName(const string& name)
{
    for (int index = 0; index < this->danhSach.size(); index++)
    {
        if (danhSach[index]->getName() == name)
        {
            /* Tìm thấy, trả về index */
            return index;
        }
    }

    /* Không tìm thấy, trả về -1 */
    return -1;
}