#include "Book.h"
Book::Book() {}
Book::Book(std::string title, std::string author)
{
	Book::Title = title;
	Book::Author = author;
}

// Not sure if works
void Book::setId(int id)
{
	Book::Id = id;
}

void Book::checkINCheckOut(bool checkedOut)
{
	CheckedOut = checkedOut;
}
std::string Book::getTitle()
{
	return Book::Title;
}
std::string Book::getAuthor() 
{
	return Book::Author;
}
int Book::getId() 
{
	return Book::Id;
}
void Book::setTitle(std::string title)
{
	Book::Title = title;
}
void Book::setAuthor(std::string author)
{
	Book::Author = author;
}
bool Book::getCheckedOutStatus()
{
	return Book::CheckedOut;
}