#ifndef CUCKOOHASHTABLE_H
#define CUCKOOHASHTABLE_H

#include <iostream>
#include <vector>
#include <string>
#include <functional>

template <typename T>
class CuckooHashTable {
private:
    std::vector<T> table1;
    std::vector<T> table2;
    std::vector<bool> ocupado1;
    std::vector<bool> ocupado2;
    size_t capacidade;
    size_t elementos;
    const double FATOR_CARGA = 0.5;

    // Funções hash otimizadas
    size_t hash1(const T& data) {
        std::hash<std::string> hasher;
        return hasher(data.marca + data.nome) % capacidade;
    }

    size_t hash2(const T& data) {
        std::hash<std::string> hasher;
        return hasher(data.nome + data.marca) % capacidade;
    }

    void resize() {
        size_t novaCapacidade = capacidade * 2;
        std::vector<T> elementosAtuais;

        // Coleta todos os elementos
        for (size_t i = 0; i < capacidade; i++) {
            if (ocupado1[i]) elementosAtuais.push_back(table1[i]);
            if (ocupado2[i]) elementosAtuais.push_back(table2[i]);
        }

        // Redimensiona as tabelas
        capacidade = novaCapacidade;
        table1.resize(capacidade);
        table2.resize(capacidade);
        ocupado1.assign(capacidade, false);
        ocupado2.assign(capacidade, false);
        elementos = 0;

        // Reinsere os elementos
        for (const auto& data : elementosAtuais) inserir(data);
    }

public:
    CuckooHashTable() : capacidade(10), elementos(0) {
        table1.resize(capacidade);
        table2.resize(capacidade);
        ocupado1.resize(capacidade, false);
        ocupado2.resize(capacidade, false);
    }

    void inserir(T data) {
        if (elementos >= capacidade * FATOR_CARGA) resize();

        T current = data;
        int tentativas = 0;

        while (tentativas < capacidade * 2) {
            size_t idx1 = hash1(current);
            if (!ocupado1[idx1]) {
                table1[idx1] = current;
                ocupado1[idx1] = true;
                elementos++;
                return;
            }
            std::swap(current, table1[idx1]);

            size_t idx2 = hash2(current);
            if (!ocupado2[idx2]) {
                table2[idx2] = current;
                ocupado2[idx2] = true;
                elementos++;
                return;
            }
            std::swap(current, table2[idx2]);

            tentativas++;
        }

        resize();
        inserir(current);
    }

    bool buscar(T data, int& passos) {
        passos = 1;
        size_t idx1 = hash1(data);
        if (ocupado1[idx1] && table1[idx1].marca == data.marca &&
            table1[idx1].nome == data.nome) return true;

        passos++;
        size_t idx2 = hash2(data);
        if (ocupado2[idx2] && table2[idx2].marca == data.marca &&
            table2[idx2].nome == data.nome) return true;

        return false;
    }

    void exibir() {
        std::cout << "\n=== CUCKOO HASH TABLE ===\n";
        for (size_t i = 0; i < capacidade; i++) {
            if (ocupado1[i]) {
                std::cout << "[T1][" << i << "] " << table1[i].marca
                          << " " << table1[i].nome << "\n";
            }
            if (ocupado2[i]) {
                std::cout << "[T2][" << i << "] " << table2[i].marca
                          << " " << table2[i].nome << "\n";
            }
        }
    }
};

#endif