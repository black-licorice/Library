#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <functional>
#include "Book.h"
#include "Inventory.h"
#include "User.h"

Inventory _inventory;
std::vector<User> _users;
User _loggedIn;


void listOptions();
void addNewBook();
void listAllBooks();
void checkInOut(std::string inOut);
void deleteBookByTitle();
void displayCheckedOutBooks();
void createUser();
void listUsers();
int Login();
void loadUsers();
void loadBooks();
void saveBooks();
std::string m_sub_str(std::string str, int from, int to);


int main()
{
    loadUsers();
    loadBooks();
    while (true)
    {
        int loginSuccess = Login();
        if (loginSuccess == 0)
        {
            break;
        }
    }
    while (true) 
    {
        listOptions();
        int input;
        std::cin >> input;
        std::cin.ignore();
        switch (input)
        {
        case 0:
            _inventory.saveBooks();
            main();
        case 1:
        {
            listAllBooks();
            break;
        }
        case 2:
        {
            checkInOut("out");
            break;
        }
        case 3:
        {
            checkInOut("in");
            break;
        }
        case 4:
        {
            if (_loggedIn.Role != Role::Member)
                addNewBook();
            else
                std::cout << "Invalid Input";
            break;

        }
        case 5:
        {
            if (_loggedIn.Role != Role::Member)
                deleteBookByTitle();
            else
                std::cout << "Invalid Input";
            break;
        }
        case 6:
        {
            if (_loggedIn.Role != Role::Member)
                displayCheckedOutBooks(); 
            else
                std::cout << "Invalid Input";
            break;
        }
        case 7:
            if (_loggedIn.Role != Role::Member)
                createUser();
            else
                std::cout << "You are not permitted to do That";
            break;
        case 8:
            if (_loggedIn.Role != Role::Member)
                listUsers();
            else
                std::cout << "You are not permitted to do That";

        default:
            std::cout << "Invalid Input";
            break;
        }
    }
}
/*
*AUTH FUNCTIONS*
*/
int Login() {
    std::cout << "Enter Username: ";
    std::string username;
    getline(std::cin, username);
    User user;
    user.Username = username;


    std::vector<User>::iterator it = find(_users.begin(), _users.end(), user);
    if (it == _users.end())
    {
        std::cout << "User not found" << std::endl;
        return 1;
    }
    User temp = _users[it - _users.begin()];

    std::cout << "Enter Password: ";
    std::string password;
    getline(std::cin, password);
    std::hash<std::string> str_hash;
    unsigned int hashed = str_hash(password);

    if (hashed == temp.hashedPass) {
        _loggedIn = _users[it - _users.begin()];
        return 0;
    }
    std::cout << "Incorect password" << std::endl;
    return 1;

}
/*
* HELPER FUNCTIONS *
*/
void listOptions() {
    std::cout << "Choose an option:" << std::endl;

    if(_loggedIn.Role != Role::Member)
    {
        std::cout << "1. List books" << std::endl;
        std::cout << "2. Check out book" << std::endl;
        std::cout << "3. Return book" << std::endl;
        std::cout << "4. Add book" << std::endl;
        std::cout << "5. Delete book" << std::endl;
        std::cout << "6. List all checked out books" << std::endl;
        std::cout << "7. Create a new user" << std::endl;
        std::cout << "8. List all users" << std::endl;
    }
    else {
        std::cout << "1. List books" << std::endl;
        std::cout << "2. Check out book" << std::endl;
        std::cout << "3. Return book" << std::endl;

    }
    std::cout << "0. Exit" << std::endl;
}
void addNewBook()
{
    std::cout << "Title: ";
    std::string title;
    std::string author;
    getline(std::cin, title);
    std::cout << "Author: ";
    getline(std::cin, author);
    Book newBook(title, author);
    _inventory.addBook(newBook);
    saveBooks();
}
void listAllBooks()
{
    std::cout << "ID\tTITLE\tAUTHOR" << std::endl;

    int n = _inventory.getVBooksSize();
    for (int i = 0; i < n; i++)
    {
        Book book = _inventory.getCopyAtIndex(i);
        if (book.getTitle().length() != 0 && book.getAuthor().length() != 0)
            std::cout << book.getId() << "\t" << book.getTitle() << "\t" << book.getAuthor() << std::endl;
    }
    std::cout << std::endl;
}
void checkInOut(std::string inOut)
{
    std::cout << (inOut == "out" ? "Book to be Checked Out: " : "Book to be Returned: ");
    std::string title;
    getline(std::cin, title);
    _inventory.checkInOutByTitle(title, inOut);
    saveBooks();
}
void deleteBookByTitle()
{
    std::cout << "Title: ";
    std::string title;
    getline(std::cin, title);
    _inventory.removeBookByTitle(title);
}
void displayCheckedOutBooks()
{
    int n = _inventory.getVBooksSize();
    for (int i = 0; i < n; i++)
    {
        Book book = _inventory.getCopyAtIndex(i);
        if (book.getCheckedOutStatus())
        {
            std::cout << book.getId() << "\t" << book.getTitle() << "\t" << book.getAuthor() << std::endl;
        }
    }
}
void createUser()
{
    int _maxUserID = _users.size() != 0 ? _users.back().Id : 0;
    User newUser;
    std::cout << "Please select a role for the new account or press 0 to exit" << std::endl;
    std::cout << "1. Admin" << std::endl;
    std::cout << "2. Employee" << std::endl;
    std::cout << "3. Member" << std::endl;
    int role;
    while (!(std::cin >> role)) {
        std::cout << "Invalid input!" << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::cin.ignore();
    std::string roleStr;
    switch (role)
    {
    case 0:
        return;
    case 1:
        newUser.Role = Role::Admin;
        roleStr = "Admin";
        break;
    case 2:
        newUser.Role = Role::Employee;
        roleStr = "Employee";
        break;
    case 3:
        newUser.Role = Role::Member;
        roleStr = "Member";
        break;
    default:
        std::cout << "Invalid input" << std::endl;
        return;
    }
    std::cout << "First name: ";
    getline(std::cin, newUser.FirstName);
    std::cout << "\nLast name: ";
    getline(std::cin, newUser.LastName);
    std::cout << "\nUsername: ";
    getline(std::cin, newUser.Username);
    std::cout << "\nPassword: ";
    std::string unHashedPass;
    getline(std::cin, unHashedPass);
    std::hash<std::string> str_hash;
    newUser.hashedPass = str_hash(unHashedPass);
    newUser.Id = _maxUserID + 1;
    if (newUser.hashedPass == NULL || newUser.Username.length() == 0)
    {
        std::cout << "Username or Password is Missing" << std::endl;
        createUser();
    }
    _users.push_back(newUser);

    std::ofstream oFile("users.csv", std::fstream::binary | std::fstream::out | std::fstream::app);
    oFile << newUser.Id << "," << newUser.Username << "," << role << "," << newUser.FirstName << "," << newUser.LastName << ',' <<  newUser.hashedPass << std::endl;
    oFile.close();
}
void listUsers()
{
    std::cout << "ID\tFIRST NAME\tLAST NAME\tUSERNAME\tROLE" << std::endl;

    int n = _users.size();
    for (int i = 0; i < n; i++)
    {
        User user = _users[i]; 
        if (user.Username.length() == 0) // if current user is the _loggedIn global
            continue;

        std::string role;
        switch (user.Role) 
        {
        case Role::Admin:
            role = "Admin";
            break;
        case Role::Employee :
            role = "Employee";
            break;
        case Role::Member:
            role = "Member";
            break;
        }
        std::cout << user.Id << "\t" << user.FirstName << "\t" << user.LastName << "\t" << user.Username << "\t" << role << std::endl;
    }
    std::cout << std::endl;
}
/*
* FILE RELATED FUNCTIONS *
*/
void loadUsers() 
{
    std::ifstream iFile("users.csv");
    std::string lineData[6];
    std::string userLine;
    while (!iFile.eof())
    {
        getline(iFile, userLine);
        std::size_t prevFound = 0;
        std::size_t found = userLine.find(',', prevFound);
        for (int i = 0; i < 6; i++)
        {
            lineData[i] = m_sub_str(userLine, prevFound, found);
            prevFound = found + 1;
            found = userLine.find(',', prevFound);
        }

        User loadedUser;
        std::stringstream s_to_i(lineData[0]);
        s_to_i >> loadedUser.Id;
        loadedUser.Username = lineData[1];
        s_to_i.clear();
        std::stringstream s_to_i_role(lineData[2]);
        int role = 0;
        s_to_i_role >> role;


        switch (int(role))
        {
        case 1:
            loadedUser.Role = Role::Admin;
            break;
        case 2:
            loadedUser.Role = Role::Employee;
            break;
        case 3:
            loadedUser.Role = Role::Member;
            break;
        }
        loadedUser.FirstName = lineData[3];
        loadedUser.LastName = lineData[4];
        s_to_i.clear();
        s_to_i << lineData[5];
        s_to_i >> loadedUser.hashedPass;
        _users.push_back(loadedUser);
    }
}
void loadBooks()
{
    std::ifstream iFile("books.csv");
    std::string lineData[4];
    std::string bookLine;
    while (!iFile.eof())
    {
        getline(iFile, bookLine);
        std::size_t prevFound = 0;
        std::size_t found = bookLine.find(',', prevFound);
        for (int i = 0; i < 4; i++)
        {
            lineData[i] = m_sub_str(bookLine, prevFound, found);
            prevFound = found + 1;
            found = bookLine.find(',', prevFound);
        }

        Book loadedBook;
        loadedBook.setTitle(lineData[1]);
        loadedBook.setAuthor(lineData[2]);
        std::stringstream s_to_i(lineData[3]);
        int checkedOutCase;
        s_to_i >> checkedOutCase;
        if (checkedOutCase > 0) 
        {
            loadedBook.checkINCheckOut(true);
        }
        _inventory.addBook(loadedBook);
    }
}
void saveBooks()
{
    _inventory.saveBooks();
}
std::string m_sub_str(std::string str, int from, int to)
{
    std::stringstream res;
    if (to != -1) 
    {
        for (int i = from; i < to; i++)
        {
            res << str[i];
        }
    }
    else 
    {
        for (int i = from - 1; i < str.length(); i++)
        {
            res << str[i];
        }
    }
    
    return res.str();
}