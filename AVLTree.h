#ifndef AVLTREE_H
#define AVLTREE_H

#include <iostream>
#include <iomanip>
#include <algorithm>
#include "DataHandler.h"

template <typename T>
class AVLTree {
private:
    struct Node {
        T data;
        Node* left;
        Node* right;
        int height;
        Node(T data) : data(data), left(nullptr), right(nullptr), height(1) {}
    };

    Node* root;

    // Funções auxiliares
    int height(Node* node) { return node ? node->height : 0; }
    int balanceFactor(Node* node) { return height(node->right) - height(node->left); }

    void updateHeight(Node* node) {
        node->height = 1 + std::max(height(node->left), height(node->right));
    }

    Node* rotateRight(Node* y) {
        Node* x = y->left;
        y->left = x->right;
        x->right = y;
        updateHeight(y);
        updateHeight(x);
        return x;
    }

    Node* rotateLeft(Node* x) {
        Node* y = x->right;
        x->right = y->left;
        y->left = x;
        updateHeight(x);
        updateHeight(y);
        return y;
    }

    Node* balance(Node* node) {
        if (balanceFactor(node) == 2) {
            if (balanceFactor(node->right) < 0) node->right = rotateRight(node->right);
            return rotateLeft(node);
        }
        if (balanceFactor(node) == -2) {
            if (balanceFactor(node->left) > 0) node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
        return node;
    }

    // Função para encontrar o nó mínimo
    Node* findMin(Node* node) {
        return node->left ? findMin(node->left) : node;
    }

    // Inserção
    Node* insertRec(Node* node, T data) {
        if (!node) return new Node(data);
        if (data.nome < node->data.nome) node->left = insertRec(node->left, data);
        else node->right = insertRec(node->right, data);
        updateHeight(node);
        return balance(node);
    }

    // Remoção
    Node* removeRec(Node* node, T data) {
        if (!node) return nullptr;

        // Busca pelo nó
        if (data.nome < node->data.nome) {
            node->left = removeRec(node->left, data);
        } else if (data.nome > node->data.nome) {
            node->right = removeRec(node->right, data);
        } else {
            // Nó encontrado: deletar
            if (!node->left || !node->right) {
                Node* temp = node->left ? node->left : node->right;
                if (!temp) {
                    temp = node;
                    node = nullptr;
                } else {
                    *node = *temp; // Copia conteúdo
                }
                delete temp;
            } else {
                // Nó com dois filhos: substituir pelo sucessor in-order
                Node* temp = findMin(node->right);
                node->data = temp->data;
                node->right = removeRec(node->right, temp->data);
            }
        }

        // Balancear após remoção
        if (!node) return node;
        updateHeight(node);
        return balance(node);
    }

    // Busca com contagem de passos
    bool searchRec(Node* node, const T& alvo, int& passos) {
        if (!node) return false;
        passos++; // Conta cada passo

        if (node->data.marca == alvo.marca &&
            node->data.nome == alvo.nome &&
            node->data.preco == alvo.preco &&
            node->data.revenda == alvo.revenda &&
            node->data.ano == alvo.ano) return true;

        if (alvo.nome < node->data.nome) return searchRec(node->left, alvo, passos);
        else return searchRec(node->right, alvo, passos);
    }

    // Exibição em ordem
    void printInOrder(Node* node) {
        if (node) {
            printInOrder(node->left);
            std::cout << std::left << std::setw(15) << node->data.marca
                      << std::setw(20) << node->data.nome
                      << std::fixed << std::setprecision(2) << std::setw(12) << node->data.preco
                      << std::fixed << std::setprecision(2) << std::setw(15) << node->data.revenda
                      << std::setw(6) << node->data.ano << "\n";
            printInOrder(node->right);
        }
    }

public:
    AVLTree() : root(nullptr) {}

    void inserir(T data) { root = insertRec(root, data); }

    void remover(T data) { root = removeRec(root, data); }

    bool buscar(T data, int& passos) {
        passos = 0;
        return searchRec(root, data, passos);
    }

    void exibir() {
        std::cout << "\n" << std::string(70, '-') << "\n";
        std::cout << std::left << std::setw(15) << "Marca"
                  << std::setw(20) << "Modelo"
                  << std::setw(12) << "Preço (R$)"
                  << std::setw(15) << "Revenda (R$)"
                  << std::setw(6) << "Ano\n";
        printInOrder(root);
        std::cout << std::string(70, '-') << "\n";
    }

    ~AVLTree() {
        // Destrutor opcional (implementar se necessário)
    }
};

#endif