#include "stack.h"
#include <iostream>

using namespace std;

Stack::Stack(int size) {
  this->size = size;
  this->index = 0;
  ptr = new int[size];
}

Stack::Stack(const Stack &s) {
  size = s.size;
  this->index = 0;
  ptr = new int[size];
  for (int i = 0; i < size; i++) {
    ptr[i] = s.ptr[i];
  }
}

Stack::Stack(Stack &&s) {
  size = s.size;
  this->index = 0;
  ptr = s.ptr;
  // delete [] a nullptr is safe
  s.ptr = nullptr;
}

Stack::~Stack() { delete[] ptr; }

Stack &Stack::operator=(const Stack &s) {
  if (this == &s)
    return *this;

  delete[] ptr; // bug fix1: perform deep copy instead of ptr = s.ptr;size =
                // s.size;index = 0;
  ptr = new int[s.size];
  size = s.size;
  index = s.index;
  for (int i = 0; i < index; i++) {
    ptr[i] = s.ptr[i];
  }
  return *this;
}

Stack &Stack::operator=(Stack &&s) {
  // bug fix2: deep copy instead of *this = s
  if (this == &s)
    return *this;

  delete[] ptr; // Free the existing resource.
  ptr = s.ptr;
  size = s.size;
  index = s.index;

  s.ptr = nullptr;
  s.size = 0; // Set size and index to safe values.
  s.index = 0;
  return *this;
}

void Stack::push(int val) {
  if (index < size)
    ptr[index++] = val;
}

int Stack::pop() {
  if (!index)
    return -1;
  return ptr[--index];
}

int Stack::top() {
  if (!index)
    return -1;
  return ptr[index - 1];
}

bool Stack::empty() { return !index; }