#include "stack.h"

Node::Node(int32_t value, Node* previous) : value(value), previous(previous) {
}

Stack::Stack() : head_(nullptr), size_(0) {
}

Stack::~Stack() {
    Node* cur = head_;
    while (cur != nullptr) {
        Node* prev = cur->previous;
        delete cur;
        cur = prev;
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
    size_ = 0;
    this->~Stack();
    head_ = nullptr;
}

bool Stack::Empty() const {
    return size_ == 0;
}
