#pragma once
#include <string>
#include <vector>
#include "Book.h"

class BookManagement
{
private:
    std::vector<Book*> books;
	BookManagement() {};	/* Hàm khởi tạo mặc định không làm gì hết */

public:
    // Không cho phép copy
    BookManagement(const BookManagement&) = delete;
    BookManagement& operator=(const BookManagement&) = delete;

    /* Hàm static */
    static BookManagement& getInstance();
	std::vector<Book*>& getDanhSachBooks();

    /* Menu quản lý sách */
	void Menu();

    void addBook();
    void removeBook(const std::string& isbn);
    void XuatDanhSachBooks() const;

    /* Các hàm tìm kiếm */
    int findISBN(const std::string& isbn);
    int findName(const std::string& name);

    /* Các hàm load và store data */
	static void loadFromCsv(const std::string& filename = "books.csv");  /* Mặc định là books.csv */
	static void storeToCsv(const std::string& filename = "books.csv");   /* Mặc định là books.csv */
};

