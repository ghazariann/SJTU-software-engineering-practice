#pragma once

#include <cassert>
#include <cstddef>

template <typename T>
class Stack {
   private:
    struct node {
        T data;
        node *next;
        node(const T &x, node *N = NULL) {
            data = x;
            next = N;
        }
        node() : next(NULL) {}
        ~node() {}
    };
    node *top_p;
    int currSize;

   public:
    Stack() {
        top_p = NULL;
        currSize = 0;
    }

    ~Stack() {
        node *tmp;
        while (top_p != NULL) {
            tmp = top_p;
            top_p = top_p->next;
            delete tmp;
        }
        currSize = 0;
    }

    int size() const{
        return currSize;
    }

    bool empty() const {
        return size() == 0;
    }

    void push(T t) {
        top_p = new node(t, top_p);
        currSize++;
    }

    T pop() {
        node *tmp = top_p;  // need this line to delete pointer (59)
        T x = tmp->data;
        top_p = top_p->next;
        delete tmp;
        currSize--;
        return x;
    }
    T get(int index) const {  // index = 0 is the top of the stack
        node *tmp = top_p;
        for (int i = 0; i < index; i++) {
            tmp = tmp->next;
        }
        return tmp->data;
    }
    T &top() const {
        return top_p->data;
    }
};
