#include "Book.h"
#include "book_ultis.h"

using namespace std;

Book::Book(const string& isbn, const string& name, const string& author, const string& nxb, const int& year, const string& category, const double& importPrice, const double& sellingPrice, const int& soLuong)
{
	this->isbn = isbn;
	this->name = name;
	this->author = author;
	this->nxb = nxb;
	this->year = year;
	this->category = category;
	this->importPrice = importPrice;
	this->sellingPrice = sellingPrice;
	this->soLuong = soLuong;
}

/* Getter functions */
string Book::getIsbn() const
{
	return this->isbn;
}

string Book::getName() const
{
	return this->name;
}

string Book::getAuthor() const
{
	return this->author;
}

string Book::getNxb() const
{
	return this->nxb;
}

int Book::getYear() const
{
	return this->year;
}

string Book::getCategory() const
{
	return this->category;
}

double Book::getImportPrice() const
{
	return this->importPrice;
}

double Book::getSellingPrice() const
{
	return this->sellingPrice;
}

int Book::getSoLuong() const
{
	return this->soLuong;
}
