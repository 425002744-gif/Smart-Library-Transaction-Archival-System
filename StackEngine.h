#ifndef STACK_ENGINE_H
#define STACK_ENGINE_H

#include "EntityModel.h"

struct StackNode {
    Book data;
    StackNode* next;
    StackNode(Book b) : data(b), next(nullptr) {}
};

class StackEngine {
private:
    StackNode* topNode;
    int count;

public:
    StackEngine();
    ~StackEngine();

    void push(const Book& book);
    Book pop();
    Book peek() const;
    bool isEmpty() const;
    int getCount() const;
    void displayStack() const;
    void clear();
};

#endif // STACK_ENGINE_H
