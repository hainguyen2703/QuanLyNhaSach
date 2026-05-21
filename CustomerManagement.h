#pragma once
#include <vector>
#include "KhachHang.h"

class CustomerManagement
{
private: 
	std::vector<KhachHang*> danhSach;
	CustomerManagement() {};	/* Hàm khởi tạo mặc định không làm gì hết */
public:
    // Không cho phép copy
    CustomerManagement(const CustomerManagement&) = delete;
    CustomerManagement& operator=(const CustomerManagement&) = delete;

    // Hàm truy cập instance duy nhất
    static CustomerManagement& getInstance();
    void themKhachHang(KhachHang* kh);
    std::vector<KhachHang*>& getDanhSach();
    int getSoLuongKH();
    void XuatDanhSachKH();
    void XoaKhachHang(const int& index);

    /* Menu quản lý khách hàng */
    void Menu();

    void addCustomer();

    /* Các hàm tìm kiếm */
    int findPhone(const string& phone);
	int findMail(const string& mail);
    vector<KhachHang*> findName(const string& name);
    int findID(const string& id);

    /* Các hàm load và store data */
    static void loadFromCsv(const std::string& filename = "CustomerData.csv");  /* Mặc định là CustomerData.csv */
    static void storeToCsv(const std::string& filename = "CustomerData.csv");   /* Mặc định là CustomerData.csv */
};

