//
// Created by Maxim on 05.04.2022.
//

#ifndef COURSE_WORK_4TH_MYLIST_H
#define COURSE_WORK_4TH_MYLIST_H

#include <cstdio>

template<class T>
struct Node {
    T data;
    Node<T>* prev;
    Node<T>* next;
};

template<class T>
class MyList {

private:
    Node<T>* head;
    Node<T>* tail;
    size_t count;

public:
    MyList() : count(0) {
        head = nullptr;
        tail = nullptr;
    }

    ~MyList() {
        clear();
    }

    bool empty();
    size_t size();
    void clear();
    void push_back( const T& value );
    void pop_back();
    void push_front( const T& value );
    void pop_front();

    class Iterator {
    private:
        Node<T>* current;

    public:
        explicit Iterator(Node<T>* pointer) : current(pointer) {}

        ~Iterator() = default;

        Node<T>& operator+ (size_t n) {
            while (n--) {
                auto tmp = current->next;
                current = tmp;
            }
            return *current;
        }

        Node<T>& get_current() {
            return *current;
        }

        Node<T>& operator- (size_t n) {
            while (n--) {
                auto tmp = current->prev;
                current = tmp;
            }
            return *current;
        }

        Node<T>& operator++ (int) {
            auto tmp = current->next;
            current = tmp;
            return *(current);
        }

        Node<T>& operator-- (int) {
            auto tmp = current->prev;
            current = tmp;
            return *(current);
        }

        Node<T>& operator++ () {
            auto retrn = *current;
            current = current->next;
            return (retrn);
        }
        Node<T>& operator-- () {
//            current = current->prev;
            return *(current)->prev;
        }

        bool operator!=(const Iterator& iter) {return current != iter.current;}
        bool operator==(const Iterator& iter) {return current == iter.current;}
        Node<T>& operator* () {return *current;}

    };

    Iterator begin() {
        return Iterator(tail);
    }

    Iterator end() {
        return Iterator(head);
    }
};

template<class T>
bool MyList<T>::empty() {
    return !(count);
}

template<class T>
size_t MyList<T>::size() {
    return count;
}

template<class T>
void MyList<T>::clear() {
    while (!empty()) {
        pop_back();
    }
}

template<class T>
void MyList<T>::push_back(const T &value) {
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
void MyList<T>::pop_back() {
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
void MyList<T>::push_front(const T &value) {
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
void MyList<T>::pop_front() {
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


#endif //COURSE_WORK_4TH_MYLIST_H
