//
// Created by Pedro on 24/05/2025.
//

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

template <typename T>
class LinkedList {
private:
    struct Node {
        T data;
        Node* next;
        Node(T data) : data(data), next(nullptr) {}
    };
    Node* head;

public:
    LinkedList() : head(nullptr) {}
    void inserir(T data);
    void remover(T data);
    bool buscar(T data);
    void exibir();
    ~LinkedList();
};

#endif