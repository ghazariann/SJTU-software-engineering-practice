#pragma once
#include <cassert>
#include <cstddef>

template <typename T>
class Queue {
   private:
    struct node {
        T data;
        node *next;
        node(const elemType &x, node *N = nullptr) {
            data = x;
            next = N;
        }
        node() : next(nullptr) {}
        ~node() {}
    };
    node *front, *rear;
    int size;

   public:
    Queue() {
        front = rear = nullptr;
        size = 0;
    }

    ~Queue() {
        node *tmp;
        while (front != nullptr) {
            tmp = front;
            front = front->next;
            delete tmp;
        }
    }

    int size() const {
        return size;
    }

    bool empty() const {
        return size() == 0;
    }

    void push(T t) {
    if (rear == nullptr)
        front = rear = new node(t);
    else
        rear = rear->next = new node(t);
    size++;
    }

    void pop() {
        node *tmp = front;
        T value = front->data;
        front = front->next;
        if (front == nullptr) rear = nullptr;  // 最后一个元素出队
        delete tmp;
        return value;
        size--;
    }

    T &front() const {
        return front->data;
    }

    T &back() const {
        return rear->data;
    }
};
