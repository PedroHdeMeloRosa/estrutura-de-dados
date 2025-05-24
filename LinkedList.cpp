//
// Created by Pedro on 24/05/2025.
//

#include "LinkedList.h"
#include <iostream>
#include "DataHandler.h"

template <typename T>
void LinkedList<T>::inserir(T data) {
    Node* novoNode = new Node(data);
    novoNode->next = head;
    head = novoNode;
}

template <typename T>
bool LinkedList<T>::buscar(T data) {
    Node* atual = head;
    while (atual != nullptr) {
        if (atual->data.modelo == data.modelo) // Comparação por modelo
            return true;
        atual = atual->next;
    }
    return false;
}

template <typename T>
void LinkedList<T>::exibir() {
    Node* atual = head;
    while (atual != nullptr) {
        std::cout << "Modelo: " << atual->data.modelo
                  << ", Preço: " << atual->data.preco << std::endl;
        atual = atual->next;
    }
}

template <typename T>
LinkedList<T>::~LinkedList() {
    Node* atual = head;
    while (atual != nullptr) {
        Node* proximo = atual->next;
        delete atual;
        atual = proximo;
    }
}

// Instanciação explícita para evitar erros de linkagem
template class LinkedList<Moto>;