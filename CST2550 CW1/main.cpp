#include <iostream>
#include <vector>
#include <string>
#include <ctime>

using namespace std;

//classess 
class Person {
private:
    string name;
    string address;
    string email;

public:
    Person(string name, string address, string email) : name(name), address(address), email(email) {}

    // accessor methods
    string getName() const { return name; }
    string getAddress() const { return address; }
    string getEmail() const { return email; }

    // mutator methods
    void setName(string n) { name = n; }
    void setAddress(string a) { address = a; }
    void setEmail(string e) { email = e; }
};

//classess
class Book {
private:
    int bookID;
    string bookName;
    string authorFirstName;
    string authorLastName;
    string bookType;
    Person borrower;
    int memberId;
    string dueDate;

public:
    Book(int i, string n, string aF, string aL, string t, Person b, int m, string d)
        : bookID(i), bookName(n), authorFirstName(aF), authorLastName(aL), bookType(t), borrower(b), memberId(m), dueDate(d) {}

    // Accessor methods
    int getBookID() const { return bookID; }
    string getBookName() const { return bookName; }
    string getAuthorFirstName() const { return authorFirstName; }
    string getAuthorLastName() const { return authorLastName; }
    string getBookType() const { return bookType; }
    Person getBorrower() const { return borrower; }
    int getMemberId() const { return memberId; }
    string getDueDate() const { return dueDate; }

    // Mutator methods
    void setBookID(int i) { bookID = i; }
    void setBookName(string n) { bookName = n; }
    void setAuthorFirstName(string aF) { authorFirstName = aF; }
    void setAuthorLastName(string aL) { authorLastName = aL; }
    void setBookType(string t) { bookType = t; }
    void setBorrower(Person b) { borrower = b; }
    void setMemberId(int m) { memberId = m; }
    void setDueDate(string d) { dueDate = d; }

    void returnBook() {
        borrower = Person("", "", "");
        memberId = 0;
    }

    void borrowBook(Person borrower, int memberId, string dueDate) {
        this->borrower = borrower;
        this->memberId = memberId;
        this->dueDate = dueDate;
    }
};

class Librarian : public Person {
private:
    int staffID;
    int salary;

public:
    Librarian(int id, string n, string a, string e, int s, int sal) : Person(n, a, e), staffID(id), salary(sal) {}

    // Accessor methods
    int getStaffID() const { return staffID; }
    int getSalary() const { return salary; }

    // Mutator methods
    void setStaffID(int id) { staffID = id; }
    void setSalary(int sal) { salary = sal; }

    // library functionality 
    void addMember(Person& member) {
        // add a new member
        cout << "New member added:\n";
        cout << "Name: " << member.getName() << "\nAddress: " << member.getAddress() << "\nEmail: " << member.getEmail() << endl;
    }

    void issueBook(Book& book, int memberID) {
        // issue a book to a member
        time_t now = time(0);
        struct tm dueDateStruct = *localtime(&now);
        dueDateStruct.tm_mday += 3; // Due date is set to 3 days from the current date
        char dueDate[11];
        strftime(dueDate, sizeof(dueDate), "%Y-%m-%d", &dueDateStruct);

        book.borrowBook(*this, memberID, dueDate);

        cout << "Book issued to member ID: " << memberID << " with due date: " << dueDate << endl;
    }

    void returnBook(Book& book) {
        // return a book
        cout << "Book returned by member ID: " << book.getMemberId() << endl;

        // Check if books are overdue
        time_t now = time(0);
        struct tm returnDateStruct = *localtime(&now);
        char returnDate[11];
        strftime(returnDate, sizeof(returnDate), "%Y-%m-%d", &returnDateStruct);

        if (book.getDueDate() < returnDate) {
            // Calculate fine of overdue books
            int daysOverdue = difftime(now, mktime(&returnDateStruct)) / (24 * 3600);
            int fine = daysOverdue * 1; // £1 per day overdue
            cout << "Fine for overdue book: £" << fine << endl;
        }

        book.returnBook();
    }

    void displayBorrowedBooks(int memberID, const vector<Book>& books) {
        // Implement code to display all books borrowed by an individual member
        cout << "Books borrowed by member ID: " << memberID << endl;
        for (const Book& book : books) {
            if (book.getMemberId() == memberID) {
                cout << "Book ID: " << book.getBookID() << ", Book Name: " << book.getBookName() << endl;
            }
        }
    }
};

int main() {
    // Testing the code
    Librarian librarian(1, "Brandon Espinosa", "123 Library Street", "Brandon.espinosa@library.com", 12345, 50000);
    cout << "Librarian staff ID: " << librarian.getStaffID() << endl;
    cout << "Librarian salary: " << librarian.getSalary() << endl;

    Person member("Lorena Lazo", "890 Library Street", "Lorena Lazo@library.com");
    librarian.addMember(member);

    Book book(1, "Test Book", "Casanova ", "Lazo", "Fiction", member, 2, "2022-12-31");
    librarian.issueBook(book, 2);

    librarian.returnBook(book);

    vector<Book> books = {book};
    librarian.displayBorrowedBooks(2, books);

    return 0;
}