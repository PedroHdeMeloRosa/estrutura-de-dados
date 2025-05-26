#ifndef BLOOMFILTER_H
#define BLOOMFILTER_H

#include <vector>
#include <functional>
#include <bitset>
#include <sstream>
#include "DataHandler.h"

#define BLOOM_SIZE 100000
#define NUM_HASHES 3

template <typename T>
class BloomFilter {
private:
    std::bitset<BLOOM_SIZE> bits;

    size_t hashCombined(const T& data, int seed) const {
        std::stringstream ss;
        ss << data.marca << data.nome << data.preco << data.revenda << data.ano << seed;
        return std::hash<std::string>{}(ss.str()) % BLOOM_SIZE;
    }

public:
    void inserir(const T& data) {
        for (int i = 0; i < NUM_HASHES; ++i) {
            bits.set(hashCombined(data, i));
        }
    }

    bool buscar(const T& data) const {
        for (int i = 0; i < NUM_HASHES; ++i) {
            if (!bits.test(hashCombined(data, i))) return false;
        }
        return true;
    }

    void exibir() const {
        std::cout << "\n⚠️ Bloom Filter - Elementos aproximados: "
                  << bits.count() / NUM_HASHES << "\n";
    }
};

#endif