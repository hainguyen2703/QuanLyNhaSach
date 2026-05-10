#include <vector>
#include "UserManagement.h"

using namespace std;

/* Khởi tạo số lượng mặc định bằng 0 */
int UserManagement::soLuong = 0;

/* Hàm truy cập instance duy nhất */
UserManagement& UserManagement::getInstance() {
    static UserManagement instance; // tạo 1 lần duy nhất
    return instance;
}

/* Hàm thêm một khách hàng mới */
void UserManagement::themKhachHang(KhachHang* kh) {
    this->danhSach.push_back(kh);
    this->soLuong++;
}

/* Hàm lấy danh sách khách hàng */
vector<KhachHang*>& UserManagement::getDanhSach() {
    return this->danhSach;
}

int UserManagement::getSoLuongKH()
{
    return soLuong;
}