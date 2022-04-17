//
// Created by Maxim on 05.04.2022.
//

#ifndef COURSE_WORK_4TH_MY_LIST_H
#define COURSE_WORK_4TH_MY_LIST_H

#include <cstdio>

template<class T>
struct Node {
    T data;
    Node<T>* prev;
    Node<T>* next;
};

template<class T>
class my_list {

private:
    Node<T>* head;
    Node<T>* tail;
    size_t count;

public:
    my_list() : count(0) {
        head = nullptr;
        tail = nullptr;
    }

    ~my_list() {
        clear();
    }

    bool empty();
    size_t size();
    void clear();
    void push_back( const T& value );
    void pop_back() noexcept;
    void push_front( const T& value );
    void pop_front() noexcept;

    class iterator {
        Node<T>* current;
    public:
        explicit iterator(Node<T>* pointer) : current(pointer) {}
        ~iterator() = default;

        iterator operator+ (size_t n) {
            while (n--) current = current->next;
            return iterator(current);
        }
        iterator operator- (size_t n) {
            while (n--) current = current->prev;
            return iterator(current);
        }
//        postfix (x++)
        iterator operator++ (int) {
            auto return_value = current;
            current = current->next;
            return iterator(return_value);
        }
        iterator operator-- (int) {
            auto return_value = current;
            current = current->prev;
            return iterator(return_value);
        }
//        prefix (++x)
        iterator operator++ () {
            return iterator(current = current->next);
        }
        iterator operator-- () {
            return iterator(current = current->prev);
        }

        T& operator* () {
            return current->data;
        }

        bool operator== (const iterator& it) const {
            return current == it.current;
        }
        bool operator!= (const iterator& it) const {
            return current != it.current;
        }
    };

    iterator begin() noexcept {
        return iterator(tail);
    }
    iterator end() noexcept {
        return iterator(head->next);
    }
};

template<class T>
bool my_list<T>::empty() {
    return !(count);
}

template<class T>
size_t my_list<T>::size() {
    return count;
}

template<class T>
void my_list<T>::clear() {
    while (!empty()) {
        pop_back();
    }
}

template<class T>
inline void my_list<T>::push_back(const T &value) {
    auto* tmp = new Node<T>;
    tmp->data = value;
    tmp->next = nullptr;
    if (!head)
        head = tail = tmp;
    else {
        head->next = tmp;
        tmp->prev = head;
        head = tmp;
    }
    count++;
}

template<class T>
void my_list<T>::pop_back() noexcept {
    if (tail == head) {
        tail = head = nullptr;
    }
    else {
        Node<T> *tmp = head->prev;
        tmp->next = nullptr;
        delete head;
        head = tmp;
    }
    count--;
}

template<class T>
void my_list<T>::push_front(const T &value) {
    auto* tmp = new Node<T>;
    tmp->data = value;
    tmp->prev = nullptr;
    if (!head)
        head = tail = tmp;
    else {
        tail->prev = tmp;
        tmp->next = tail;
        tail = tmp;
    }
    count++;
}

template<class T>
void my_list<T>::pop_front() noexcept {
    if (tail == head) {
        tail = head = nullptr;
    }
    else {
        Node<T> *tmp = tail->next;
        tmp->prev = nullptr;
        delete tail;
        tail = tmp;
    }
    count--;
}


#endif //COURSE_WORK_4TH_MY_LIST_H
