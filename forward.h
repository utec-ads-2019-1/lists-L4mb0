#ifndef FORWARD_H
#define FORWARD_H

#include "list.h"
#include "iterators/forward_iterator.h"
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

template <typename T>
class ForwardList : public List<T> {
    public:
        ForwardList() : List<T>() {
                this-> head = nullptr;
                this->tail = nullptr;
                this->nodes = 0;
        }

        T front() {
            if(this->nodes > 0){
                return this->head->data;
            }
            else throw std::out_of_range("no hay mas valores :)");
        }

        T back() {
            if(this->nodes > 0){
                return this->tail->data;
            }
            else throw std::out_of_range("no hay mas valores :)");
        }

        void push_front(T value) {
            auto * newNode =  new Node<T> (value);
            if(this->nodes > 0){
                    newNode->next = this->head;
                    this->head = newNode;
            }
            else{
                    this->head=this->tail=newNode;
                    this->tail->next= nullptr;
            }
            this->nodes++;

        }

        void push_back(T value) {
            auto * newNode =  new Node<T> (value);
            if(this->nodes > 0){
                this->tail->next = newNode;
                this->tail = newNode;
                newNode->next = nullptr;
            }
            else{
                this->head=this->tail=newNode;
                this->tail->next= nullptr;
            }
            this->nodes++;
        }

        void pop_front() {
            if(this->nodes > 0) {

                auto *sacrificio = this->head;
                this->head = this->head->next;
                if(this->nodes == 0){
                    this->tail= nullptr;
                }
                delete sacrificio;
                this->nodes--;

            }
            else throw std::out_of_range("no hay mas valores");
        }

        void pop_back() {
            if(this->nodes > 0) {
                auto *iterador = this->head;
                auto *sacrificio = this->tail;
                while (iterador->next != this->tail) {
                    iterador = iterador->next;

                    }
                    this->tail = iterador;
                    delete sacrificio;
                    this->tail->next= nullptr;
                    this->nodes--;

            }
            else throw std::out_of_range("no hay mas valores");
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
            if(this->nodes>0) {
                while(this->nodes>0) {
                    auto *sacrificio = this->head;
                    this->head = this->head->next;
                    delete sacrificio;
                    this->nodes--;
                }
                this->head = this->tail = nullptr;
            }
            else throw std::out_of_range("no hay valores");

        }

        void sort() {
            if(this->nodes>0) {
                std::vector<int> arr;
                auto *iterador = this->head;
                for (int i = 0; i < this->nodes; ++i) {
                    arr.push_back(iterador->data);
                    iterador = iterador->next;
                }
                std::sort(arr.begin(),arr.begin()+this->nodes);
                iterador = this->head;
                for (unsigned long j = 0; j < this->nodes; ++j) {
                    iterador->data = arr.at(j);
                    iterador = iterador->next;
                }
                iterador = nullptr;
                delete iterador;
            }
            else throw std::out_of_range("no hay valores (sort)");
        }
    
        void reverse() {
            if(this->nodes>0) {
                std::vector<int> arr;
                auto *iterador = this->head;
                for (int i = 0; i < this->nodes; ++i) {
                    arr.push_back(iterador->data);
                    iterador = iterador->next;
                }
                std::reverse(arr.begin(),arr.end());
                iterador = this->head;
                for (unsigned long j = 0; j < this->nodes; ++j) {
                    iterador->data = arr.at(j);
                    iterador = iterador->next;
                }
                iterador = nullptr;
                delete iterador;
            }
            else throw std::out_of_range("no hay valores (reverse)");
        }

        string name() {
            return "Forward List";
        }
        ForwardIterator<T> begin() {
            return ForwardIterator<T>(this->head);

        }

	    ForwardIterator<T> end() {
            return ForwardIterator<T>(this->tail->next);
        }

        void merge(ForwardList<T> list) {
            for (int i = 0; i < list.size(); ++i) {
                this->push_back(list[i]);
            }
        }
};

#endif