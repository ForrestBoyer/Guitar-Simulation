#ifndef CIRCULARBUFFER_HPP_
#define CIRCULARBUFFER_HPP_
// Copyright 2022 Forrest Boyer

#include <queue>
#include <exception>
#include <stdexcept>
#include <iostream>

template<typename T>
class CircularBuffer {
 public:
    explicit CircularBuffer(size_t capacity) {
        try {
            if (capacity >= 1) {
                max_capacity = capacity;
            } else {
                throw std::invalid_argument("Capacity must be at least 1");
            }
        } catch (std::invalid_argument& err) {
            std::cerr << "exception: " << err.what() << std::endl;
            throw;
        }
    }

    size_t size() const {
        return q.size();
    }

    bool isEmpty() const {
        return q.empty();
    }
    bool isFull() const {
        if (static_cast<int>(q.size()) == static_cast<int>(max_capacity)) {
            return true;
        } else {
            return false;
        }
    }

    void enqueue(T item) {
        try {
            if (isFull()) {
                throw std::runtime_error("List is full");
            } else {
            q.push(item);
            }
        } catch (std::runtime_error& err) {
            std::cerr << "exception: " << err.what() << std::endl;
            throw;
        }
    }

    T dequeue() {
        try {
            if (isEmpty()) {
                throw std::runtime_error("List is empty");
            } else {
                T ret = q.front();
                q.pop();
                return ret;
            }
        } catch (std::runtime_error& err) {
            std::cerr << "exception: " << err.what() << std::endl;
            throw;
        }
        return -1;
    }

    T peek() const {
        try {
            if (isEmpty()) {
                throw std::runtime_error("List is empty");
            } else {
                return q.front();
            }
        } catch (std::runtime_error& err) {
            std::cerr << "exception: " << err.what() << std::endl;
            throw;
        }
        return -1;
    }

 private:
    std::queue<T> q;
    int max_capacity;
};
#endif  // CIRCULARBUFFER_HPP_
