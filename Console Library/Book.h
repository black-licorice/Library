#pragma once
#include <iostream>
class Book
{
private:
	int Id;
	std::string Title;
	std::string Author;
	bool CheckedOut = false;
public:
	Book(); // general builder func, returns an empty book
	Book(std::string title, std::string author);
	void setId(int id);
	void checkINCheckOut(bool checkedOut);
	std::string getTitle();
	std::string getAuthor();
	int getId();
	void setTitle(std::string title);
	void setAuthor(std::string author);
	bool getCheckedOutStatus();
	bool operator==(const Book* book)  // defines == operator functionality for Book class *** NOT CURRENTLY USED
	{
		if (Title.compare(book->Title) == 0) 
		{
			return true;
		}
		return false;
	}
};