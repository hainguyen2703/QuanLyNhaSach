#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include "BookManagement.h"
#include "common.h"

bool isbnValidate(const std::string& isbn);
void editBookMenu();
void updateISBN(Book* book);
void updateBookName(Book* book);
void updateAuthor(Book* book);
void updateNxb(Book* book);
void updateCategory(Book* book);
void updateNamXB(Book* book);
void updateSoLuong(Book* book);
void updateGiaNhap(Book* book);
void updateGiaBan(Book* book);
void deleteBook();
void khungBookInfo();