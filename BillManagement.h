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
	void taoHoaDon();
};

