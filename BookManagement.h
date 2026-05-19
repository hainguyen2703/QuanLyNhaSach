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
    BookManagement& operator=(const BookManagement&) = delete;

    /* Hàm static */
    static BookManagement getInstance();
	std::vector<Book*>& getDanhSachBooks();

    /* Menu quản lý sách */
	void bookMenu();

    void addBook();
    void addBook(const Book& book);
    void removeBook(const std::string& isbn);
    void XuatDanhSachBooks() const;

    /* Các hàm load và store data */
	void loadBooksFromFile(const std::string& filename = "books.csv");  /* Mặc định là books.csv */
	void storeBooksToFile(const std::string& filename = "books.csv");   /* Mặc định là books.csv */
};

