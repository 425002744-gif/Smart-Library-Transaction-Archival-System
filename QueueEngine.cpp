#include "QueueEngine.h"
#include <iostream>
#include <iomanip>

using namespace std;

QueueEngine::QueueEngine() : frontNode(nullptr), rearNode(nullptr), count(0) {}

QueueEngine::~QueueEngine() {
    clear();
}

bool QueueEngine::isEmpty() const {
    return frontNode == nullptr;
}

int QueueEngine::getCount() const {
    return count;
}

void QueueEngine::enqueue(const string& patronId, const string& isbn, const string& date) {
    QueueNode* newNode = new QueueNode(patronId, isbn, date);
    if (isEmpty()) {
        frontNode = rearNode = newNode;
    } else {
        rearNode->next = newNode;
        rearNode = newNode;
    }
    count++;
}

void QueueEngine::dequeue() {
    if (isEmpty()) {
        cout << "\n[Error: Queue Underflow! No active reservations in line.]\n";
        return;
    }
    QueueNode* temp = frontNode;
    frontNode = frontNode->next;
    if (frontNode == nullptr) {
        rearNode = nullptr;
    }
    delete temp;
    temp = nullptr;
    count--;
}

QueueNode QueueEngine::peekFront() const {
    if (isEmpty()) {
        return QueueNode("N/A", "N/A", "N/A");
    }
    return *frontNode;
}

void QueueEngine::displayQueue() const {
    if (isEmpty()) {
        cout << "\n[Reservation Queue is currently empty.]\n";
        return;
    }
    cout << "\n=========================================================================\n";
    cout << "                   BOOK RESERVATION QUEUE (FIFO LINE)                    \n";
    cout << "=========================================================================\n";
    cout << left << setw(18) << "Patron ID"
              << setw(15) << "Book ISBN"
              << setw(20) << "Request Date" << "\n";
    cout << "-------------------------------------------------------------------------\n";

    QueueNode* current = frontNode;
    while (current != nullptr) {
        cout << left << setw(18) << current->patronId
                  << setw(15) << current->isbn
                  << setw(20) << current->requestDate << "\n";
        current = current->next;
    }
    cout << "=========================================================================\n";
}

void QueueEngine::clear() {
    while (!isEmpty()) {
        dequeue();
    }
}
