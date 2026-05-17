#include <iostream>
#include <vector>
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
    /* Xuất thông tin của khách hàng */
    for (KhachHang* kh : this->danhSach)
    { 
        cout << kh->getID() << '|' << kh->getName() << "|" << kh->getPhone() << '|' << kh->getMail() << '|';
        cout << kh->getAddress() << '|' << getDateString(kh->getRegisterDate()) << '|' << kh->getType() << endl;
    }
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