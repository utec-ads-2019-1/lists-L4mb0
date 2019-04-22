#ifndef NODE_H
#define NODE_H

template <typename T>
struct Node {
    T data;
    Node<T>* next;
    Node<T>* prev;

    Node(T data){
        this->data = data;
        this->next = nullptr;
    }

    void genocidio() {
        while(next != nullptr){
            genocidio();
        }
        delete next;
    }
};

#endif