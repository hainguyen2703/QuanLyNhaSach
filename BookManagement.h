#pragma once
#include <string>
#include <vector>
#include "Book.h"

class BookManagement
{
private:
    std::vector<Book*> books;
	BookManagement() {};	/* Hàm khởi tạo mặc định không làm gì hết */
    int soLuongTheoTheLoai(const std::string& category);

public:
    // Không cho phép copy
    BookManagement(const BookManagement&) = delete;
    BookManagement& operator=(const BookManagement&) = delete;

    /* Hàm static */
    static BookManagement& getInstance();
	std::vector<Book*>& getDanhSachBooks();

    /* Menu quản lý sách */
	void Menu();

    /* Các hàm thêm/xóa/xuất danh sách sách */
    void addBook();
    void removeBook(const int& index);
    void XuatDanhSachBooks() const;
    Book* getBookByIsbn(const std::string& isbn);

    /* Các hàm tìm kiếm */
    int findISBN(const std::string& isbn);
    std::vector<Book*> findName(const std::string& name);

    /* Thống kê sách */
    std::vector<std::string> listCategory();
    int TongSoLuongSach();
    void thongKeByCategory();
    void listOutOfStock();

    /* Các hàm load và store data */
	static void loadFromCsv(const std::string& filename = "books.csv");  /* Mặc định là books.csv */
	static void storeToCsv(const std::string& filename = "books.csv");   /* Mặc định là books.csv */

    /* Destructor */
    ~BookManagement();
};

