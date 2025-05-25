#ifndef BLOOMFILTER_H
#define BLOOMFILTER_H

#include <vector>
#include <functional>
#include <bitset>
#include "DataHandler.h"

#define BLOOM_SIZE 100000 // Tamanho do filtro (ajuste conforme necessidade)
#define NUM_HASHES 3      // Número de funções hash

template <typename T>
class BloomFilter {
private:
    std::bitset<BLOOM_SIZE> bits;

    // Funções hash (usando combinação de hash de strings)
    size_t hash1(const T& data) {
        std::string chave = data.marca + data.nome;
        return std::hash<std::string>{}(chave) % BLOOM_SIZE;
    }

    size_t hash2(const T& data) {
        std::string chave = data.nome + data.marca;
        return std::hash<std::string>{}(chave) % BLOOM_SIZE;
    }

    size_t hash3(const T& data) {
        std::string chave = data.marca + std::to_string(data.ano);
        return std::hash<std::string>{}(chave) % BLOOM_SIZE;
    }

public:
    void inserir(T data) {
        bits.set(hash1(data));
        bits.set(hash2(data));
        bits.set(hash3(data));
    }

    bool buscar(T data) {
        return bits.test(hash1(data)) &&
               bits.test(hash2(data)) &&
               bits.test(hash3(data));
    }

    // Bloom Filter não suporta remoção!
    void exibir() {
        std::cout << "\n⚠️ Bloom Filter não exibe elementos individuais!\n";
    }
};

#endif