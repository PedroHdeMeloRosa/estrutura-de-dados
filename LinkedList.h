#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include "DataHandler.h"

template <typename T>
class LinkedList {
private:
    struct Node {
        T data;
        Node* next;
        Node(T data) : data(data), next(nullptr) {}
    };
    Node* head;

    // Busca recursiva por todos os campos
    int buscarExatoRecursivo(Node* atual, const T& alvo, int posicao) {
        if (!atual) return -1; // Fim da lista

        // Verifica todos os campos
        if (
            atual->data.marca == alvo.marca &&
            atual->data.nome == alvo.nome &&
            atual->data.preco == alvo.preco &&
            atual->data.revenda == alvo.revenda &&
            atual->data.ano == alvo.ano
        ) {
            return posicao;
        }

        return buscarExatoRecursivo(atual->next, alvo, posicao + 1);
    }

public:
    LinkedList() : head(nullptr) {}

    void inserir(T data) {
        Node* novoNode = new Node(data);
        novoNode->next = head;
        head = novoNode;
    }

    void remover(T data) {
        Node* atual = head;
        Node* anterior = nullptr;

        while (atual) {
            if (atual->data.marca == data.marca &&
                atual->data.nome == data.nome &&
                atual->data.preco == data.preco &&
                atual->data.revenda == data.revenda &&
                atual->data.ano == data.ano) {

                if (anterior) anterior->next = atual->next;
                else head = atual->next;

                delete atual;
                return;
                }
            anterior = atual;
            atual = atual->next;
        }
    }

    // Busca por todos os campos
    int buscar(const T& alvo) {
        return buscarExatoRecursivo(head, alvo, 1); // Posições começam em 1
    }

    void exibir() {
        Node* atual = head;
        std::cout << std::left << std::setw(15) << "Marca"
                  << std::setw(20) << "Modelo"
                  << std::setw(12) << "Preço (R$)"
                  << std::setw(15) << "Revenda (R$)"
                  << std::setw(6) << "Ano" << "\n"
                  << std::string(70, '-') << "\n";

        while (atual) {
            std::cout << std::left
                      << std::setw(15) << atual->data.marca
                      << std::setw(20) << atual->data.nome
                      << std::fixed << std::setprecision(2) << std::setw(12) << atual->data.preco
                      << std::fixed << std::setprecision(2) << std::setw(15) << atual->data.revenda
                      << std::setw(6) << atual->data.ano << "\n";
            atual = atual->next;
        }
    }

    ~LinkedList() {
        Node* atual = head;
        while (atual) {
            Node* proximo = atual->next;
            delete atual;
            atual = proximo;
        }
    }
};

#endif