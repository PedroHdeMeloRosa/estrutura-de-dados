#ifndef DATAHANDLER_H
#define DATAHANDLER_H

#include <vector>
#include <string>

struct Moto {
    std::string marca;
    std::string nome;
    double preco;
    double revenda;
    int ano;
};

class DataHandler {
public:
    static std::vector<Moto> lerDataset(const std::string& caminho);
};

#endif