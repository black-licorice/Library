#include "Inventory.h"
#include <string>
#include <sstream>
#include <fstream>
/*
* PRIVATE FUNCTIONS
*/

Book* Inventory::m_getBookById(int Id, std::string title) {
	for (int i = 0; i < Inventory::m_Books.size(); i++)
	{
		if (Inventory::m_Books[i].getId() == Id)
			return &Inventory::m_Books[i];
	}
	std::cout << "The selected ID is not valid" << std::endl;
	findBookByTitle(title);
}

/*
* PUBLIC FUNCTIONS
*/

void Inventory::addBook(Book book)
{
	Inventory::getVBooksSize() == 0 ? book.setId(1) : book.setId( Inventory::m_Books.back().getId() + 1);
	Inventory::m_Books.push_back(book);
}
int Inventory::getVBooksSize()
{
	return Inventory::m_Books.size();
}
Book Inventory::getCopyAtIndex(int index)
{
	return Inventory::m_Books[index];
}
void Inventory::removeBookByTitle(std::string title)
{
	Book* book = findBookByTitle(title);
	std::vector<Book>::iterator it = find(Inventory::m_Books.begin(), Inventory::m_Books.end(), book);
	if (it != Inventory::m_Books.end()) 
	{
		Inventory::m_Books.erase(it);
		return;
	}
}
Book* Inventory::findBookByTitle(std::string title)
{
	std::vector<Book> foundBooks;
	for (Book book : Inventory::m_Books) 
	{
		if (book.getTitle() == title) 
		{
			foundBooks.push_back(book);
		}
	}
	if (foundBooks.empty())
	{
		std::cout << title << " was not found" << std::endl;
		std::cout << "Enter another title or enter 0 to exit \n";
		std::string inputStr;
		std::cin >> inputStr;
		std::cin.ignore();
		if (inputStr == "0")
		{
			Book exit;
			return &exit; // return empty book to take advantage of its undeclared ID being negative
		}
		findBookByTitle(inputStr);
	}
	std::cout << "Results: " << std::endl;
	std::cout << "TITLE" << "\t" << "Author" << "\t" << "ID" << "\t" << "STATUS" << std::endl;
	for (int i = 0; i < foundBooks.size(); i++)
	{
		std::cout << foundBooks[i].getTitle() << "\t" << foundBooks[i].getAuthor() << "\t" << foundBooks[i].getId() << "\t" << "Currently " << (foundBooks[i].getCheckedOutStatus() ? "checked out :(" : "available :)") << std::endl;
	}
	std::cout << "Book ID : ";
	int input;
	std::cin >> input;
	std::cin.ignore();
	return Inventory::m_getBookById(input, title);

}
int Inventory::checkInOutByTitle(std::string title, std::string inOut) 
{
	bool outCondition;
	if (inOut == "out")
		outCondition = true;
	else if (inOut == "in")
		outCondition = false;
	else
	{
		std::cout << "Invalid usage of 'checkinOut' please pass 'in' or 'out' in as the second parameter" << std::endl;
		return 2;
	}
	Book* book = findBookByTitle(title);
	if (book->getId() < 0) // undeclared IDs are always negative
		return -2;
	bool outIncondition = (outCondition ? book->getCheckedOutStatus() : !book->getCheckedOutStatus()); // true if checking out while book is missing : true if returning book that has not been checked out 
	if (outIncondition)
	{
		std::cout << book->getTitle() << (outCondition ? " is already checked out" : " was never checked out") << std::endl;
		return 1;
	}
	outCondition ? book->checkINCheckOut(true) : book->checkINCheckOut(false);
	std::cout << book->getTitle() << (outCondition ? " successfully checked out" : " successfully returned") << std::endl;
	return 0;
}
void Inventory::saveBooks()
{
	std::ofstream oFile("books.csv", std::ofstream::out | std::ofstream::trunc);
	for (Book book : m_Books)
	{
		if (book.getAuthor().length() != 0 && book.getTitle().length() != 0)
			oFile << book.getId() << "," << book.getTitle() << "," << book.getAuthor() << "," << book.getCheckedOutStatus() << std::endl;
	}
	
	oFile.close();
}