#include "queue.h"

Node::Node(int32_t value, Node* next) : value(value), next(next) {
}

Queue::Queue() : front_(nullptr), tail_(nullptr), size_(0) {
}

Queue::~Queue() {
    while (size_ != 0) {
        Pop();
    }
}

void Queue::Push(int32_t value) {
    Node* new_element = new Node(value, nullptr);
    if (tail_ == nullptr) {
        tail_ = front_ = new_element;
    } else {
        tail_->next = new_element;
        tail_ = new_element;
    }
    ++size_;
}

void Queue::Pop() {
    Node* nxt = front_->next;
    delete front_;
    front_ = nxt;
    --size_;
}

int32_t Queue::Front() const {
    return front_->value;
}

int32_t Queue::Size() const {
    return size_;
}

void Queue::Clear() {
    this->~Queue();
}

bool Queue::Empty() const {
    return size_ == 0;
}
