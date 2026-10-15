#ifndef LINKED_LIST_ENGINE_H
#define LINKED_LIST_ENGINE_H

#include "EntityModel.h"

struct Node {
    Book data;
    Node* next;

    Node(Book b) : data(b), next(nullptr) {}
};

class LinkedListEngine {
private:
    Node* head;
    int size;

public:
    LinkedListEngine();
    ~LinkedListEngine();

    void insertAtTail(const Book& book);
    void insertAtHead(const Book& book);
    bool deleteByISBN(const std::string& isbn);
    Node* searchByISBN(const std::string& isbn);
    Node* searchByTitle(const std::string& title);
    bool updateBook(const std::string& isbn, const std::string& newTitle, const std::string& newAuthor, const std::string& newCategory);
    void displayCatalog() const;

    int getSize() const;
    bool isEmpty() const;
    void clear();

    Book* toDynamicArray() const;
    void updateFromSortedArray(const Book* arr, int n);
};

#endif // LINKED_LIST_ENGINE_H
