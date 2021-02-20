#pragma once
#include "Book.h"
#include <vector>
class Inventory
{
private:
	std::vector<Book> m_Books;
	Book* m_getBookById(int index, std::string title);
public:
	int getVBooksSize();
	Book getCopyAtIndex(int index);
	void addBook(Book book);
	void removeBookByTitle(std::string title);
	Book* findBookByTitle(std::string title);
	int checkInOutByTitle(std::string title, std::string inOut);
	void saveBooks();
};