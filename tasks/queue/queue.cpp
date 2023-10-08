#include "queue.h"

Node::Node(int32_t value, Node *next) : value(value), next(next) {
}

Queue::Queue() : front_(nullptr), tail_(nullptr), size_(0) {
}

Queue::~Queue() {
    Node* cur = front_;

}

void Queue::Push(int32_t value) {
}
void Queue::Pop() {
}
int32_t Queue::Front() const {
    return 0;
}
int32_t Queue::Size() const {
    return 0;
}
void Queue::Clear() {
}
bool Queue::Empty() const {
    return false;
}
