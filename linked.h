#ifndef LINKED_H
#define LINKED_H

#include "list.h"
#include "iterators/bidirectional_iterator.h"
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

template<typename T>
class LinkedList : public List<T> {
public:
    LinkedList() : List<T>() {
        this->head = nullptr;
        this->tail = nullptr;
        this->nodes = 0;

    }

    T front() {
        if (this->nodes > 0) {
            return this->head->data;
        } else throw std::out_of_range("no hay mas valores :)");
    }

    T back() {
        if (this->nodes > 0) {
            return this->tail->data;
        } else throw std::out_of_range("no hay mas valores :)");
    }

    void push_front(T value) {
        auto *newNode = new Node<T>(value);
        if (this->nodes > 0) {
            newNode->next = this->head;
            this->head->prev = newNode;
            newNode->prev = nullptr;
            this->head = newNode;
        } else {
            this->head = this->tail = newNode;
        }
        this->nodes++;

    }

    void push_back(T value) {
        auto * newNode =  new Node<T> (value);
        if(this->nodes > 0){
            newNode->prev=this->tail;
            this->tail->next = newNode;
            this->tail = newNode;
            newNode->next = nullptr;
        }
        else{
            this->head=this->tail=newNode;
        }
        this->nodes++;
    }

    void pop_front() {
        if (this->nodes > 0) {

            auto *sacrificio = this->head;
            this->head = this->head->next;
            delete sacrificio;
            this->head->prev= nullptr;
            this->nodes--;
        } else throw std::out_of_range("no hay mas valores");
    }


    void pop_back() {
        if (this->nodes > 0) {

            auto *sacrificio = this->tail;
            this->tail = this->tail->prev;
            delete sacrificio;
            this->tail->next= nullptr;
            this->nodes--;
        } else throw std::out_of_range("no hay mas valores");
    }

    T operator[](int index) {
        if(index>=this->nodes){
            throw std::out_of_range("fuera de rango");
        }
        auto * iterador = this->head;
        for (int i = 0; i < index; ++i) {
            iterador = iterador->next;
        }
        return iterador->data;

    }

    bool empty() {
        return this->nodes == 0;
    }

    int size() {
        return this->nodes;
    }

    void clear() {
        if (this->nodes > 0) {
            while (this->nodes > 0) {
                auto *sacrificio = this->head;
                this->head = this->head->next;
                delete sacrificio;
                this->nodes--;
            }
            this->head = this->tail = nullptr;
        } else throw std::out_of_range("no hay valores");

    }

    void sort() {
        if (this->nodes > 0) {
            std::vector<int> arr;
            auto *iterador = this->head;
            for (int i = 0; i < this->nodes; ++i) {
                arr.push_back(iterador->data);
                iterador = iterador->next;
            }
            std::sort(arr.begin(), arr.begin() + this->nodes);
            iterador = this->head;
            for (int j = 0; j < this->nodes; ++j) {
                iterador->data = arr.at(j);
                iterador = iterador->next;
            }
            iterador = nullptr;
            delete iterador;
        } else throw std::out_of_range("no hay valores (sort)");
    }

    void reverse() {
        auto *sacrificio = this->head;
        this->head = this->tail;
        this->tail = sacrificio;

        auto * temp = this->head;

        while(temp != nullptr) {
            sacrificio = temp->next;
            temp->next = temp->prev;
            temp->prev = sacrificio;
            temp = temp->next;
        }

        sacrificio = temp = nullptr;
        delete sacrificio, temp;
    }

    string name() {
        return "Linked List";
    }

    BidirectionalIterator<T> begin() {
        return BidirectionalIterator<T>(this->head);
    }

    BidirectionalIterator<T> end() {
        return BidirectionalIterator<T>(this->tail);
    }

    void merge(LinkedList<T> list) {
        if (list.empty()) return;;
        for (int i = 0; i < list.size(); ++i) {
            this->push_back(list[i]);
        }
    }
};

#endif