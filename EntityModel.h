#ifndef ENTITY_MODEL_H
#define ENTITY_MODEL_H

#include <string>

struct Book {
    std::string isbn;
    std::string title;
    std::string author;
    std::string category;
    bool isBorrowed;
    std::string patronId;
    std::string dueDate;

    // Default Constructor
    Book() : isbn(""), title(""), author(""), category("General"), isBorrowed(false), patronId("N/A"), dueDate("N/A") {}

    // Parameterized Constructor
    Book(std::string id, std::string t, std::string auth, std::string cat)
        : isbn(id), title(t), author(auth), category(cat), isBorrowed(false), patronId("N/A"), dueDate("N/A") {}
};

#endif // ENTITY_MODEL_H
