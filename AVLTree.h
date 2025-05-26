#ifndef AVLTREE_H
#define AVLTREE_H

#include <iostream>
#include <iomanip>
#include <algorithm>
#include <tuple>
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

    Node* findMin(Node* node) {
        return node->left ? findMin(node->left) : node;
    }

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

    Node* insertRec(Node* node, T data) {
        if (!node) return new Node(data);
        if (data < node->data) node->left = insertRec(node->left, data);
        else node->right = insertRec(node->right, data);
        updateHeight(node);
        return balance(node);
    }

    Node* removeRec(Node* node, T data) {
        if (!node) return nullptr;

        if (data < node->data) {
            node->left = removeRec(node->left, data);
        } else if (node->data < data) {
            node->right = removeRec(node->right, data);
        } else {
            if (!node->left || !node->right) {
                Node* temp = node->left ? node->left : node->right;
                if (!temp) {
                    temp = node;
                    node = nullptr;
                } else {
                    *node = *temp;
                }
                delete temp;
            } else {
                Node* temp = node->right;
                while (temp->left) temp = temp->left;
                node->data = temp->data;
                node->right = removeRec(node->right, temp->data);
            }
        }

        if (!node) return node;
        updateHeight(node);
        return balance(node);
    }

    bool searchRec(Node* node, const T& alvo, int& passos) {
        if (!node) return false;
        passos++;
        if (node->data == alvo) return true;
        return (alvo < node->data) ? searchRec(node->left, alvo, passos)
                                  : searchRec(node->right, alvo, passos);
    }

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

    bool remover(T data) {
        int dummy;
        if (!buscar(data, dummy)) return false;
        root = removeRec(root, data);
        return true;
    }

    void removerPorCriterio(Node*& node, const Moto& alvo) {
        if (!node) return;

        // Primeiro processa subárvores
        removerPorCriterio(node->left, alvo);
        removerPorCriterio(node->right, alvo);

        // Depois verifica o nó atual
        if (node->data == alvo) {
            if (!node->left || !node->right) {
                Node* temp = node->left ? node->left : node->right;
                delete node;
                node = temp;
            } else {
                Node* temp = findMin(node->right);
                node->data = temp->data;
                removerPorCriterio(node->right, temp->data);
            }
        }

        if (node) balance(node);
    }
    void removerPorCriterio(const Moto& alvo) {
        removerPorCriterio(root, alvo);
        int passosDummy;
        // Rebalanceia toda a árvore após remoções múltiplas
        while (buscar(alvo, passosDummy)) {
            root = removeRec(root, alvo);
        }
    }

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
        // Implementar destrutor se necessário
    }
};

#endif