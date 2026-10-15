#include "LinkedListEngine.h"
#include <iostream>
#include <iomanip>

using namespace std;

LinkedListEngine::LinkedListEngine() : head(nullptr), size(0) {}

LinkedListEngine::~LinkedListEngine() {
    clear();
}

bool LinkedListEngine::isEmpty() const {
    return head == nullptr;
}

int LinkedListEngine::getSize() const {
    return size;
}

void LinkedListEngine::insertAtTail(const Book& book) {
    Node* newNode = new Node(book);
    if (isEmpty()) {
        head = newNode;
    } else {
        Node* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newNode;
    }
    size++;
}

void LinkedListEngine::insertAtHead(const Book& book) {
    Node* newNode = new Node(book);
    newNode->next = head;
    head = newNode;
    size++;
}

bool LinkedListEngine::deleteByISBN(const string& isbn) {
    if (isEmpty()) return false;

    if (head->data.isbn == isbn) {
        Node* temp = head;
        head = head->next;
        delete temp;
        temp = nullptr;
        size--;
        return true;
    }

    Node* current = head;
    while (current->next != nullptr && current->next->data.isbn != isbn) {
        current = current->next;
    }

    if (current->next == nullptr) return false;

    Node* target = current->next;
    current->next = target->next;
    delete target;
    target = nullptr;
    size--;
    return true;
}

Node* LinkedListEngine::searchByISBN(const string& isbn) {
    Node* current = head;
    while (current != nullptr) {
        if (current->data.isbn == isbn) return current;
        current = current->next;
    }
    return nullptr;
}

Node* LinkedListEngine::searchByTitle(const string& title) {
    Node* current = head;
    while (current != nullptr) {
        if (current->data.title == title) return current;
        current = current->next;
    }
    return nullptr;
}

bool LinkedListEngine::updateBook(const string& isbn, const string& newTitle, const string& newAuthor, const string& newCategory) {
    Node* target = searchByISBN(isbn);
    if (target == nullptr) return false;
    target->data.title = newTitle;
    target->data.author = newAuthor;
    target->data.category = newCategory;
    return true;
}

void LinkedListEngine::displayCatalog() const {
    if (isEmpty()) {
        cout << "\n[Catalog is currently empty.]\n";
        return;
    }
    cout << "\n=========================================================================\n";
    cout << "                        LIBRARY BOOK CATALOG                             \n";
    cout << "=========================================================================\n";
    cout << left << setw(12) << "ISBN"
              << setw(22) << "Title"
              << setw(18) << "Author"
              << setw(15) << "Category"
              << setw(10) << "Status" << "\n";
    cout << "-------------------------------------------------------------------------\n";

    Node* current = head;
    while (current != nullptr) {
        cout << left << setw(12) << current->data.isbn
                  << setw(22) << current->data.title
                  << setw(18) << current->data.author
                  << setw(15) << current->data.category
                  << setw(10) << (current->data.isBorrowed ? "Borrowed" : "Available") << "\n";
        current = current->next;
    }
    cout << "=========================================================================\n";
}

void LinkedListEngine::clear() {
    Node* current = head;
    while (current != nullptr) {
        Node* nextNode = current->next;
        delete current;
        current = nextNode;
    }
    head = nullptr;
    size = 0;
}

Book* LinkedListEngine::toDynamicArray() const {
    if (isEmpty()) return nullptr;
    Book* arr = new Book[size];
    Node* current = head;
    int i = 0;
    while (current != nullptr) {
        arr[i++] = current->data;
        current = current->next;
    }
    return arr;
}

void LinkedListEngine::updateFromSortedArray(const Book* arr, int n) {
    clear();
    for (int i = 0; i < n; ++i) {
        insertAtTail(arr[i]);
    }
}
