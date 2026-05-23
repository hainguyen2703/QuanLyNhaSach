#pragma once
#include <vector>
#include "HoaDon.h"

class BillManagement
{
private:
	std::vector<HoaDon*> listHoaDon;
	BillManagement() {};
public:
	static BillManagement& getInstance();
	std::vector<HoaDon*>& getListHD();
	void taoHoaDon();

	/* Các hàm load và store data */
	static void loadFromCsv(const std::string& filename = "HoaDon.csv");  /* Mặc định là HoaDon.csv */
	static void storeToCsv(const std::string& filename = "HoaDon.csv");   /* Mặc định là HoaDon.csv */
};

