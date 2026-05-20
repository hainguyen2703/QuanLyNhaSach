#pragma once
#include <string>
#include <fstream>
#include "Book.h"
#include "KhachHang.h"

/* Function prototype */
bool isAllBlank(const std::string str);
void clearInputCache();
int getOption();
bool ktUserID(const std::string& id);
bool isAllDigit(const std::string& str);
bool phoneValidate(const std::string& phone);
bool mailValidate(const std::string& mail);
std::string toUpper(const std::string& str);
std::string toLower(const std::string& str);
std::string toLowerUtf8(const std::string& str);
void print_utf8_left(const std::string& s, int width);
int getFileSizeInByte(std::ifstream& fileInput);
KhachHang* loadUserFromCsvString(std::string& line);
Book* loadBookFromCsvString(std::string& line);