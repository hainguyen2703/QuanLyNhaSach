#include <iostream>
#include "KhachHang.h"

using namespace std;

/* Khởi tạo giá trị ban đầu cho biến Class */
int KhachHang::cntUserID = 0;

/* Khởi tạo giá trị ban đầu cho biến numOfUser */
static int numOfUser;

/* Hàm khởi tạo có tham số */
KhachHang::KhachHang(string& name, string& phone, string& mail, string& address, int& type)
{
	/* Set các thông tin đã collect từ trước */
	this->name = name;
	this->phone = phone;
	this->mail = mail;
	this->address = address;
	this->type = type;

	/* Lấy ngày hiện tại làm ngày đăng ký */
	this->ngayDK = getCurrentDate();

	/* Set ID */
	string baseID = "00000000";
	string nextID = to_string(KhachHang::cntUserID + 1);
	size_t replacePos = 8 - nextID.length();
	baseID.replace(replacePos, nextID.length(), nextID);
	this->id = "KH" + baseID;

	/* Tạo khách hàng thành công, tăng một customer */
	KhachHang::cntUserID++;
}

/********************************* Hàm set attribute **************************************/
/* Hàm set ID */
void KhachHang::setID(string& id)
{
	this->id = id;
}

/* Hàm set name */
void KhachHang::setName(string& name)
{
	this->name = name;
}

/* Ham set phone */
void KhachHang::setPhone(string& phone)
{
	this->phone = phone;
}

/* Ham set mail */
void KhachHang::setMail(string& mail)
{
	this->mail = mail;
}

/* Ham set address */
void KhachHang::setAddress(string& adr)
{
	this->address = adr;
}

/* Ham set RegisterDate */
void KhachHang::setRegisterDate(Date& date)
{
	this->ngayDK = date;
}

/* Ham set type */
void KhachHang::setType(int& type)
{
	this->type = type;
}
/*****************************************************************************************/


/********************************* Hàm get attribute *************************************/
/* Hàm get ID */
string KhachHang::getID()
{
	return this->id;
}

/* Hàm get name */
string KhachHang::getName()
{
	return this->name;
}

/* Ham get phone */
string KhachHang::getPhone()
{
	return this->phone;
}

/* Ham get mail */
string KhachHang::getMail()
{
	return this->mail;
}

/* Ham get address */
string KhachHang::getAddress()
{
	return this->address;
}

/* Ham get Date */
Date KhachHang::getRegisterDate()
{
	return this->ngayDK;
}

/* Ham get type */
int KhachHang::getType()
{
	return this->type;
}

/* Hàm get loại thẻ */
string KhachHang::getLoaiThe() const
{
	return (this->type == 1) ? "VIP" : "Normal";
}
/*****************************************************************************************/

/* Xuất thông tin khách hàng */
void KhachHang::XuatThongTin() const
{
	cout << "Mã số khách hàng: " << this->id << endl
		<< "Tên khách hàng: " << this->name << endl
		<< "Số điện thoại: " << this->phone << endl
		<< "Email: " << this->mail << endl
		<< "Địa chỉ: " << this->address << endl
		<< "Ngày đăng ký: " << getDateString(this->ngayDK) << endl
		<< "Loại thẻ: " << getLoaiThe() << endl;
}

/* Hàm sắp xếp dữ liệu để ghi file csv */
/* Thứ tự: ID, name, phone, mail, date (yyyy-mm-dd), type (string), address 
 * Lưu address cuối để không quan tâm đến các dầu phẩy trong phần address */
string KhachHang::getCsvString()
{
	return id + "|" + name + "|" + phone + "|" + mail + '|' + address + "|" + getDateCsvString(this->ngayDK) + "|" + to_string(type);
}