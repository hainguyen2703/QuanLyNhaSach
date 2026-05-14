#pragma once
#include <vector>
#include "KhachHang.h"

class UserManagement
{
private: 
	std::vector<KhachHang*> danhSach;
    static int soLuong;
	UserManagement() {};	/* Hàm khởi tạo mặc định không làm gì hết */
public:
    // Không cho phép copy
    UserManagement(const UserManagement&) = delete;
    UserManagement& operator=(const UserManagement&) = delete;

    // Hàm truy cập instance duy nhất
    static UserManagement& getInstance();
    void themKhachHang(KhachHang* kh);
    std::vector<KhachHang*>& getDanhSach();
    static int getSoLuongKH();
    void XuatDanhSachKH();
};

