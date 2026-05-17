#pragma once
#include <vector>
#include "KhachHang.h"

class UserManagement
{
private: 
	std::vector<KhachHang*> danhSach;
	UserManagement() {};	/* Hàm khởi tạo mặc định không làm gì hết */
public:
    // Không cho phép copy
    UserManagement(const UserManagement&) = delete;
    UserManagement& operator=(const UserManagement&) = delete;

    // Hàm truy cập instance duy nhất
    static UserManagement& getInstance();
    void themKhachHang(KhachHang* kh);
    std::vector<KhachHang*>& getDanhSach();
    int getSoLuongKH();
    void XuatDanhSachKH();

    /* Các hàm tìm kiếm */
    int findPhone(const string& phone);
	int findMail(const string& mail);
    int findName(const string& name);
};

