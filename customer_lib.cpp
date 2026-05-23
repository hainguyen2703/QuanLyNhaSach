#include "customer_ultis.h"
#include "CustomerManagement.h"

using namespace std;

/* Kiểm tra xem User ID có hợp lệ hay không */
bool ktUserID(const string& id)
{
	/* Kiểm tra id empty hoặc size không đủ */
	if (id.empty() || id.size() != 10)
	{
		return false;
	}

	/* Kiểm tra ID có bắt đầu bằng KH */
	string tmp = toUpper(id);

	if (tmp.rfind("KH", 0) != 0)
	{
		return false;
	}

	return true;
}

/* Hàm kiểm tra số điện thoại hợp lệ hay không */
bool phoneValidate(const string& phone)
{
	/* Kiểm tra phone input có đủ 10 chữ số */
	if (phone.size() != 10 || phone[0] != '0' || isAllDigit(phone) != true)
	{
		cout << "Số điện thoại không hợp lệ";
		return false;
	}

	/* Kiểm tra số điện thoại đã được đăng ký chưa */
	if (CustomerManagement::getInstance().findPhone(phone) != -1)
	{
		cout << "Số điện thoại đã được đăng ký!!!" << endl;
		return false;
	}

	return true;
}

/* Hàm kiểm tra mail input */
bool mailValidate(const string& mail)
{
	/* Mail không có @gmail.com và @gmail.com không phải là chuỗi kết thúc */
	if (mail.size() <= 10)
	{
		cout << "Địa chỉ mail không hợp lệ" << endl;
		return false;
	}

	string tmp = toLower(mail);
	if (tmp.rfind("@gmail.com") != (mail.size() - 10))
	{
		cout << "Địa chỉ mail không hợp lệ" << endl;
		return false;
	}

	/* Kiểm tra xem mail đã được đăng ký chưa */
	if (CustomerManagement::getInstance().findMail(tmp) != -1)
	{
		cout << "Địa chỉ mail đã được đăng ký!!!" << endl;
		return false;
	}

	/* Hợp lệ */
	return true;
}



/************************************* Edit Khách Hàng *********************************/
/* Menu chức năng edit thông tin khách hàng */
void editUserMenu()
{
	cout << setfill('=') << setw(42) << "" << endl;
	cout << setfill(' ') << setw(10) << "" << "Chỉnh sửa thông tin" << endl;
	cout << setfill('=') << setw(42) << "" << endl;
	cout << "1. Chỉnh sửa tên khách hàng" << endl;
	cout << "2. Chỉnh sửa số điện thoại" << endl;
	cout << "3. Chỉnh sửa địa chỉ" << endl;
	cout << "4. Chỉnh sửa mail" << endl;
	cout << "5. Chỉnh sửa loại thẻ" << endl;
	cout << "0. Thoát" << endl;
	cout << setw(42) << "" << endl;
}

/* Thay đổi tên khách hàng */
void editUserName(KhachHang* kh)
{
	string name;
	cout << "Nhập vào tên khách hàng mới: ";
	if(getStringLine(name) != true)
	{
		cout << "Tên không hợp lệ!!!\n";
		return;
	}

	/* Cập nhật tên khách hàng */
	kh->setName(name);
	cout << "Đã cập nhật tên khách hàng thành công!" << endl;
}

/* Thay đổi số điện thoại khách hàng */
void editUserPhone(KhachHang* kh)
{
	string phone;
	cout << "Nhập vào số điện thoại mới: ";
	/* Kiểm tra số điện thoại có hợp lệ không */
	if(getStringLine(phone) != true || phoneValidate(phone) != true)
	{
		cout << "Số điện thoại không hợp lệ" << endl;
		return;
	}

	/* Cập nhật số điện thoại khách hàng */
	kh->setPhone(phone);
	cout << "Đã cập nhật số điện thoại khách hàng thành công!" << endl;
}

/* Thay đổi địa chỉ khách hàng */ 
void editUserAddress(KhachHang* kh)
{
	string address;
	cout << "Nhập vào địa chỉ mới: ";
	if(getStringLine(address) != true)
	{
		cout << "Địa chỉ không hợp lệ" << endl;
		return;
	}
	
	/* Cập nhật địa chỉ khách hàng */
	kh->setAddress(address);
	cout << "Đã cập nhật địa chỉ khách hàng thành công!" << endl;
}

/* Thay đổi email khách hàng */
void editUserMail(KhachHang* kh)
{
	string mail;
	cout << "Nhập vào email mới: ";
	if(getStringLine(mail) != true || mailValidate(mail) != true)
	{
		cout << "Email không hợp lệ" << endl;
		return;
	}

	/* Cập nhật email khách hàng */
	kh->setMail(mail);
	cout << "Đã cập nhật email khách hàng thành công!" << endl;
}

/* Thay đổi loại thẻ khách hàng */
void editUserType(KhachHang* kh)
{
	int type;
	cout << "Nhập vào loại thẻ mới(0: Normal, 1: VIP): ";
	cin >> type;
	if (cin.fail())
	{
		cin.clear();              // xóa trạng thái lỗi
		cin.ignore(1000, '\n');   // bỏ ký tự sai trong buffer
		cout << "Loại thẻ không hợp lệ!!" << endl;
		return;
	}

	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	if (type != 0 && type != 1)
	{
		cout << "Loại thẻ không hợp lệ!!" << endl;
		return;
	}

	/* Cập nhật loại thẻ khách hàng */
	kh->setType(type);
	cout << "Đã cập nhật loại thẻ khách hàng thành công!" << endl;
}