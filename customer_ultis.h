#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include "KhachHang.h"
#include "common.h"

bool ktUserID(const std::string& id);
bool phoneValidate(const std::string& phone);
bool mailValidate(const string& mail);
void editUserMenu();
void editUserName(KhachHang* kh);
void editUserPhone(KhachHang* kh);
void editUserAddress(KhachHang* kh);
void editUserMail(KhachHang* kh);
void editUserType(KhachHang* kh);