#include "KhachHang.h"
#include "customer_ultis.h"

using namespace std;

/* Khởi tạo giá trị ban đầu cho biến Class */
int KhachHang::cntCustomerID = 0;

/* Hàm cập nhật số user id hiện tại */
void KhachHang::setCntCustomerID(const int& cnt)
{
	KhachHang::cntCustomerID = cnt;
}

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
	string nextID = to_string(KhachHang::cntCustomerID + 1);
	size_t replacePos = 8 - nextID.length();
	baseID.replace(replacePos, nextID.length(), nextID);
	this->id = "KH" + baseID;

	/* Tạo khách hàng thành công, tăng một customer */
	KhachHang::cntCustomerID++;
}

/* Hàm tạo khách hàng mới */
KhachHang* KhachHang::createNewKhachHang()
{
	/* 1. Họ tên */
	string hoten;	/* Biến chứa tên khách hàng */
	cout << setw(30) << setfill('*') << "*" << endl;
	cout << "Tạo tài khoảng" << endl;
	cout << setw(30) << setfill('*') << "" << endl;
	cout << "Họ tên khách hàng: ";
	if(getStringLine(hoten) != true) return NULL;

	/* 2. Số điện thoại */
	string phone;
	cout << "Số điện thoại: ";
	/* Kiểm tra phone input */
	if (getStringLine(phone) != true || phoneValidate(phone) == false)
		return NULL;

	/* 3. Mail */
	string mail;
	cout << "Mail: ";
	/* Kiểm tra mail input */
	if (getStringLine(mail) != true || mailValidate(mail) != true)
		return NULL;
	else
		mail = toLower(mail);

	/* 4. Địa chỉ */
	string address;
	cout << "Địa chỉ: ";
	if(getStringLine(address) != true)
	{
		cout << "Địa chỉ không hợp lệ!!\n";
		return NULL;
	}

	/* 5. Loại thẻ */
	int the;
	cout << "Loại thẻ (0: Thường, 1: VIP): ";
	cin >> the;
	cin.ignore(100, '\n');
	if (the != 0 && the != 1)
	{
		cout << "Không hợp lệ!!" << endl;
		cout << "Mặc định hạng thẻ thường!!!" << endl;
		the = 0;
	}

	/* Tạo user mới */
	return new KhachHang(hoten, phone, mail, address, the);
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
	this->mail = toLower(mail);
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
	print_utf8_left(this->id, 15);
	cout << "|";
	print_utf8_left(this->name, 30);
	cout << "|";
	print_utf8_left(this->phone, 15);
	cout << "|";
	print_utf8_left(this->mail, 30);
	cout << "|";
	print_utf8_left(this->address, 40);
	cout << "|";
	print_utf8_left(getDateString(this->ngayDK), 15);
	cout << "|";
	print_utf8_left(getLoaiThe(), 12);
	cout << "|" << endl;
}

/* Hàm sắp xếp dữ liệu để ghi file csv */
/* Thứ tự: ID, name, phone, mail, date (yyyy-mm-dd), type (string), address 
 * Lưu address cuối để không quan tâm đến các dầu phẩy trong phần address */
string KhachHang::getCsvString()
{
	return id + "|" + name + "|" + phone + "|" + mail + '|' + address + "|" + getDateCsvString(this->ngayDK) + "|" + to_string(type);
}