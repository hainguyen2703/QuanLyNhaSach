#pragma once
#include <string>

class Book
{
private:
	std::string isbn;
	std::string name;
	std::string author;
	std::string nxb;
	std::string category;
	int year;
	int soLuong;
	double importPrice;
	double sellingPrice;
	
public:
	/* Hàm khởi tạo có tham số */
	Book(const std::string& isbn, const std::string& name, const std::string& author, const std::string& nxb, const int& year, const std::string& category, const double& importPrice, const double& sellingPrice, const int& soLuong);

	static Book* createNewBook();

	/* Các hàm getter và setter */
	std::string getIsbn();
	std::string getName() const;
	std::string getAuthor() const; 
	std::string getNxb() const;
	int getYear() const;
	std::string getCategory() const;
	double getImportPrice() const;
	double getSellingPrice() const;
	int getSoLuong() const;

	void setIsbn(const std::string& isbn);
	void setName(const std::string& name);
	void setAuthor(const std::string& author);
	void setNxb(const std::string& nxb);
	void setYear(const int& year);
	void setCategory(const std::string& category);
	void setImportPrice(const double& importPrice);
	void setSellingPrice(const double& sellingPrice);

	/* Hàm xuất thông tin sách */
	void XuatThongTin() const;

	/* Hàm format để store data xuống csv */
	std::string getCsvString() const;
};

