#include "StackEngine.h"
#include <iostream>
#include <iomanip>

using namespace std;

StackEngine::StackEngine() : topNode(nullptr), count(0) {}

StackEngine::~StackEngine() {
    clear();
}

bool StackEngine::isEmpty() const {
    return topNode == nullptr;
}

int StackEngine::getCount() const {
    return count;
}

void StackEngine::push(const Book& book) {
    StackNode* newNode = new StackNode(book);
    newNode->next = topNode;
    topNode = newNode;
    count++;
}

Book StackEngine::pop() {
    if (isEmpty()) {
        cout << "\n[Error: Stack Underflow! No returned books to process.]\n";
        return Book();
    }
    StackNode* temp = topNode;
    Book poppedBook = temp->data;
    topNode = topNode->next;
    delete temp;
    temp = nullptr;
    count--;
    return poppedBook;
}

Book StackEngine::peek() const {
    if (isEmpty()) {
        return Book();
    }
    return topNode->data;
}

void StackEngine::displayStack() const {
    if (isEmpty()) {
        cout << "\n[Return Drop Stack is empty.]\n";
        return;
    }
    cout << "\n=========================================================================\n";
    cout << "                     RECENTLY RETURNED BOOKS (LIFO STACK)                \n";
    cout << "=========================================================================\n";
    cout << left << setw(12) << "ISBN"
              << setw(25) << "Title"
              << setw(20) << "Patron ID" << "\n";
    cout << "-------------------------------------------------------------------------\n";

    StackNode* current = topNode;
    while (current != nullptr) {
        cout << left << setw(12) << current->data.isbn
                  << setw(25) << current->data.title
                  << setw(20) << current->data.patronId << "\n";
        current = current->next;
    }
    cout << "=========================================================================\n";
}

void StackEngine::clear() {
    while (!isEmpty()) {
        pop();
    }
}
