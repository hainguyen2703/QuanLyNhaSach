#pragma once
#include <string>

/* Function prototype */
bool isAllBlank(const std::string str);
void clearInputCache();
int getOption();
bool ktUserID(const std::string& id);
bool phoneValidate(const std::string& phone);
bool mailValidate(const std::string& mail);
std::string toUpper(const std::string& str);
std::string toLower(const std::string& str);
std::string toLowerUtf8(const std::string& str);
