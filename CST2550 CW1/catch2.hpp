#define CATCH_CONFIG_MAIN
#include "catch2.hpp"
#include "main.cpp" // Assuming your implementation is in this file
#include <iostream>

TEST_CASE("Person Class Test") {
    Person person("Brandon Espinosa", "123 Library Street", "Brandon.espinosa@library.com");

    REQUIRE(person.getName() == "Brandon Espinosa");
    REQUIRE(person.getAddress() == "123 Library Street");
    REQUIRE(person.getEmail() == "Brandon.espinosa@library.com");

    person.setName("Lorena Lazo");
    person.setAddress("890 Library Street");
    person.setEmail("Lorena.Lazo@library.com");

    REQUIRE(person.getName() == "Lorena Lazo");
    REQUIRE(person.getAddress() == "890 Library Street");
    REQUIRE(person.getEmail() == "Lorena.Lazo@library.com");
}

TEST_CASE("Book Class Test") {
    Person borrower("Brandon Espinosa", "123 Library Street", "Brandon.espinosa@library.com");
    Book book(1, "Test Book", "Casanova", "Lazo", "Fiction", borrower, 2, "2022-12-31");

    REQUIRE(book.getBookID() == 1);
    REQUIRE(book.getBookName() == "Test Book");
    REQUIRE(book.getAuthorFirstName() == "Casanova");
    REQUIRE(book.getAuthorLastName() == "Lazo");
    REQUIRE(book.getBookType() == "Fiction");
    REQUIRE(book.getBorrower() == borrower);
    REQUIRE(book.getMemberId() == 2);
    REQUIRE(book.getDueDate() == "2022-12-31");

    book.returnBook();

    REQUIRE(book.getBorrower().getName() == "");
    REQUIRE(book.getMemberId() == 0);
    REQUIRE(book.getDueDate() == "");

    book.borrowBook(borrower, 3, "2023-02-01");

    REQUIRE(book.getBorrower() == borrower);
    REQUIRE(book.getMemberId() == 3);
    REQUIRE(book.getDueDate() == "2023-02-01");
}

TEST_CASE("Librarian Class Test") {
    Person borrower("Brandon Espinosa", "123 Library Street", "Brandon.espinosa@library.com");
    Person member("Lorena Lazo", "890 Library Street", "Lorena.Lazo@library.com");
    Librarian librarian(1, "Brandon Espinosa", "123 Library Street", "Brandon.espinosa@library.com", 12345, 50000);

    librarian.addMember(member);

    REQUIRE(librarian.getStaffID() == 1);
    REQUIRE(librarian.getSalary() == 50000);

    Book book(1, "Test Book", "Casanova", "Lazo", "Fiction", borrower, 2, "2022-12-31");

    librarian.issueBook(book, 2);

    REQUIRE(book.getBorrower() == borrower);
    REQUIRE(book.getMemberId() == 2);
    REQUIRE(book.getDueDate() == "2023-02-03");

    librarian.returnBook(book);

    REQUIRE(book.getBorrower().getName() == "");
    REQUIRE(book.getMemberId() == 0);
    REQUIRE(book.getDueDate() == "");

    std::vector<Book> books = {book};
    librarian.displayBorrowedBooks(2, books);

    REQUIRE(books.empty() == true);
}