//
// Created by Pedro on 24/05/2025.
//

#ifndef DATAHANDLER_H
#define DATAHANDLER_H

#include <string>
#include <vector>

// Estrutura para armazenar dados das motos
struct Moto {
    std::string marca;
    std::string modelo;
    double preco;
    double preco_revenda;
    int ano;
};

class DataHandler {
public:
    static std::vector<Moto> lerDataset(const std::string& caminho);
};

#endif
