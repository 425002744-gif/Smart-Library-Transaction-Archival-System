#ifndef QUEUE_ENGINE_H
#define QUEUE_ENGINE_H

#include "EntityModel.h"

struct QueueNode {
    std::string patronId;
    std::string isbn;
    std::string requestDate;
    QueueNode* next;

    QueueNode(std::string pId, std::string bIsbn, std::string date)
        : patronId(pId), isbn(bIsbn), requestDate(date), next(nullptr) {}
};

class QueueEngine {
private:
    QueueNode* frontNode;
    QueueNode* rearNode;
    int count;

public:
    QueueEngine();
    ~QueueEngine();

    void enqueue(const std::string& patronId, const std::string& isbn, const std::string& date);
    void dequeue();
    QueueNode peekFront() const;
    bool isEmpty() const;
    int getCount() const;
    void displayQueue() const;
    void clear();
};

#endif // QUEUE_ENGINE_H
