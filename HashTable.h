#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include <iomanip>
#include <vector>
#include <list>
#include <sstream>
#include <algorithm>
#include "DataHandler.h"

template <typename T>
class HashTable {
private:
    struct Node {
        T data;
        Node(const T& data) : data(data) {}
    };

    std::vector<std::list<Node>> table;
    size_t capacidade;
    size_t elementos;
    const double FATOR_CARGA_MAX = 0.7;

    size_t hashFunction(const T& data) const {
        std::stringstream ss;
        ss << data.marca << data.nome << data.preco << data.revenda << data.ano;
        return std::hash<std::string>{}(ss.str()) % capacidade;
    }

    void resize() {
        size_t novaCapacidade = capacidade * 2 + 1;
        std::vector<std::list<Node>> novaTabela(novaCapacidade);

        for (auto& bucket : table) {
            for (auto& node : bucket) {
                size_t novoIndex = hashFunction(node.data) % novaCapacidade;
                novaTabela[novoIndex].push_back(node);
            }
        }

        table = std::move(novaTabela);
        capacidade = novaCapacidade;
    }

public:
    HashTable() : capacidade(101), elementos(0) {
        table.resize(capacidade);
    }

    void inserir(const T& data) {
        if ((elementos + 1.0) / capacidade > FATOR_CARGA_MAX) {
            resize();
        }

        size_t index = hashFunction(data) % capacidade;
        table[index].emplace_back(data);
        elementos++;
    }

    bool remover(const T& data) {
        bool removido = false;
        size_t index = hashFunction(data) % capacidade;
        auto& bucket = table[index];

        for (auto it = bucket.begin(); it != bucket.end();) {
            if (it->data == data) {
                it = bucket.erase(it);
                elementos--;
                removido = true;
            } else {
                ++it;
            }
        }
        return removido;
    }

    bool buscar(const T& data, int& passos) const {
        passos = 0;
        size_t index = hashFunction(data) % capacidade;

        for (const auto& node : table[index]) {
            passos++;
            if (node.data == data) return true;
        }
        return false;
    }

    void exibir() const {
        std::cout << "\n=== TABELA HASH (" << elementos << "/" << capacidade << ") ===\n";
        std::cout << std::left << std::setw(15) << "Marca"
                  << std::setw(20) << "Modelo"
                  << std::setw(12) << "Preço (R$)"
                  << std::setw(15) << "Revenda (R$)"
                  << std::setw(6) << "Ano\n"
                  << std::string(70, '-') << "\n";

        for (const auto& bucket : table) {
            for (const auto& node : bucket) {
                const auto& m = node.data;
                std::cout << std::left << std::setw(15) << m.marca
                          << std::setw(20) << m.nome
                          << std::fixed << std::setprecision(2) << std::setw(12) << m.preco
                          << std::fixed << std::setprecision(2) << std::setw(15) << m.revenda
                          << std::setw(6) << m.ano << "\n";
            }
        }
        std::cout << std::string(70, '-') << "\n";
    }
};

#endif