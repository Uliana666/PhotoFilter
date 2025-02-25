#include "stack.h"

Node::Node(int32_t value, Node* previous) : value(value), previous(previous) {
}

Stack::Stack() : head_(nullptr), size_(0) {
}

Stack::~Stack() {
    while (size_ != 0) {
        Pop();
    }
}

void Stack::Push(int32_t value) {
    head_ = new Node(value, head_);
    ++size_;
}

void Stack::Pop() {
    Node* prev = head_->previous;
    delete head_;
    head_ = prev;
    --size_;
}

int32_t Stack::Top() const {
    return head_->value;
}

int32_t Stack::Size() const {
    return size_;
}

void Stack::Clear() {
    this->~Stack();
}

bool Stack::Empty() const {
    return size_ == 0;
}
