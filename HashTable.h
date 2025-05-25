#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include <iomanip>
#include <vector>
#include <list>
#include <algorithm>
#include "DataHandler.h"

template <typename T>
class HashTable {
private:
    struct Node {
        T data;
        Node(T data) : data(data) {}
    };

    std::vector<std::list<Node>> table;
    size_t capacidade;
    size_t elementos;
    const double FATOR_CARGA_MAX = 0.7;

    // Função hash usando método da multiplicação
    size_t hashFunction(const std::string& chave) {
        const double A = 0.6180339887; // Constante áurea
        size_t hash = 0;
        for (char c : chave) hash = 31 * hash + c;
        double frac = hash * A - static_cast<int>(hash * A);
        return static_cast<size_t>(capacidade * frac);
    }

    // Redimensiona a tabela quando necessário
    void resize() {
        size_t novaCapacidade = capacidade * 2;
        std::vector<std::list<Node>> novaTabela(novaCapacidade);

        for (auto& bucket : table) {
            for (auto& node : bucket) {
                size_t novoIndex = hashFunction(node.data.marca + node.data.nome) % novaCapacidade;
                novaTabela[novoIndex].push_back(node);
            }
        }

        table = std::move(novaTabela);
        capacidade = novaCapacidade;
    }

public:
    HashTable() : capacidade(10), elementos(0) {
        table.resize(capacidade);
    }

    void inserir(T data) {
        if ((elementos + 1) > capacidade * FATOR_CARGA_MAX) {
            resize();
        }

        size_t index = hashFunction(data.marca + data.nome) % capacidade;
        table[index].emplace_back(data);
        elementos++;
    }

    bool buscar(T data, int& passos) {
        passos = 0;
        size_t index = hashFunction(data.marca + data.nome) % capacidade;

        for (const auto& node : table[index]) {
            passos++;
            if (node.data.marca == data.marca &&
                node.data.nome == data.nome &&
                node.data.preco == data.preco &&
                node.data.revenda == data.revenda &&
                node.data.ano == data.ano) {
                return true;
            }
        }
        return false;
    }

    void remover(T data) {
        size_t index = hashFunction(data.marca + data.nome) % capacidade;
        auto& bucket = table[index];
        auto it = std::find_if(bucket.begin(), bucket.end(), [&](const Node& node) {
            return node.data.marca == data.marca &&
                   node.data.nome == data.nome &&
                   node.data.preco == data.preco &&
                   node.data.revenda == data.revenda &&
                   node.data.ano == data.ano;
        });

        if (it != bucket.end()) {
            bucket.erase(it);
            elementos--;
        }
    }

    void exibir() {
        std::cout << "\n=== TABELA HASH (" << elementos << "/" << capacidade << ") ===\n";
        std::cout << std::left << std::setw(15) << "Marca"
                  << std::setw(20) << "Modelo"
                  << std::setw(12) << "Preço (R$)"
                  << std::setw(15) << "Revenda (R$)"
                  << std::setw(6) << "Ano\n"
                  << std::string(70, '-') << "\n";

        for (const auto& bucket : table) {
            for (const auto& node : bucket) {
                std::cout << std::left
                          << std::setw(15) << node.data.marca
                          << std::setw(20) << node.data.nome
                          << std::fixed << std::setprecision(2) << std::setw(12) << node.data.preco
                          << std::fixed << std::setprecision(2) << std::setw(15) << node.data.revenda
                          << std::setw(6) << node.data.ano << "\n";
            }
        }
        std::cout << std::string(70, '-') << "\n";
    }
};

#endif