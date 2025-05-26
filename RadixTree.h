#ifndef RADIXTREE_H
#define RADIXTREE_H

#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <iomanip>
#include <algorithm>
#include "DataHandler.h"

template <typename T>
class RadixTree {
private:
    struct Node {
        std::string prefix;
        std::unordered_map<char, Node*> children;
        std::vector<T> data;
        bool isEnd;

        Node(const std::string& pr) : prefix(pr), isEnd(false) {}
    };

    Node* root;

    void split(Node* node, const std::string& commonPrefix, size_t splitPos) {
        Node* splitNode = new Node(node->prefix.substr(splitPos));
        splitNode->children = node->children;
        splitNode->isEnd = node->isEnd;
        splitNode->data = node->data;

        node->prefix = commonPrefix;
        node->children.clear();
        node->children[splitNode->prefix[0]] = splitNode;
        node->isEnd = false;
        node->data.clear();
    }

    bool insert(Node* node, const std::string& key, const T& value, size_t depth) {
        size_t i = 0;
        while (i < node->prefix.length() && i + depth < key.length() &&
               node->prefix[i] == key[i + depth]) i++;

        if (i < node->prefix.length()) {
            split(node, node->prefix.substr(0, i), i);
            depth += i;
        } else {
            depth += node->prefix.length();
        }

        if (depth == key.length()) {
            if (std::find(node->data.begin(), node->data.end(), value) == node->data.end()) {
                node->data.push_back(value);
            }
            node->isEnd = true;
            return true;
        }

        char nextChar = key[depth];
        if (!node->children.count(nextChar)) {
            node->children[nextChar] = new Node(key.substr(depth));
            node->children[nextChar]->data.push_back(value);
            node->children[nextChar]->isEnd = true;
            return true;
        }

        return insert(node->children[nextChar], key, value, depth);
    }

    bool search(Node* node, const std::string& key, const T& target, size_t depth, int& steps) const {
        steps++;
        size_t i = 0;
        while (i < node->prefix.length() && i + depth < key.length() &&
               node->prefix[i] == key[i + depth]) i++;

        if (i != node->prefix.length()) return false;
        depth += i;

        if (depth == key.length()) {
            if (!node->isEnd) return false;
            return std::find(node->data.begin(), node->data.end(), target) != node->data.end();
        }

        char nextChar = key[depth];
        if (!node->children.count(nextChar)) return false;
        return search(node->children[nextChar], key, target, depth, steps);
    }

    void print(Node* node, const std::string& currentPrefix) const {
        if (node->isEnd) {
            for (const auto& item : node->data) {
                std::cout << std::left << std::setw(15) << item.marca
                          << std::setw(20) << item.nome
                          << std::fixed << std::setprecision(2) << std::setw(12) << item.preco
                          << std::fixed << std::setprecision(2) << std::setw(15) << item.revenda
                          << std::setw(6) << item.ano << "\n";
            }
        }
        for (const auto& pair : node->children) {
            print(pair.second, currentPrefix + node->prefix);
        }
    }

public:
    RadixTree() : root(new Node("")) {}

    void inserir(const T& value) {
        insert(root, value.nome, value, 0);
    }

    bool buscar(const T& target, int& passos) const {
        passos = 0;
        return search(root, target.nome, target, 0, passos);
    }

    void exibir() const {
        std::cout << "\n" << std::string(70, '-') << "\n";
        std::cout << std::left << std::setw(15) << "Marca"
                  << std::setw(20) << "Modelo"
                  << std::setw(12) << "Preço (R$)"
                  << std::setw(15) << "Revenda (R$)"
                  << std::setw(6) << "Ano\n";
        print(root, "");
        std::cout << std::string(70, '-') << "\n";
    }
};

#endif