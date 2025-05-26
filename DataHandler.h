#ifndef DATAHANDLER_H
#define DATAHANDLER_H

#include <vector>
#include <string>
#include <tuple>

struct Moto {
    std::string marca;
    std::string nome;
    float preco;
    float revenda;
    int ano;

    // Operador de igualdade para buscas exatas
    bool operator==(const Moto& outra) const {
        return std::tie(marca, nome, preco, revenda, ano) ==
               std::tie(outra.marca, outra.nome, outra.preco, outra.revenda, outra.ano);
    }

    // Operador de comparação para ordenação na AVL
    bool operator<(const Moto& outra) const {
        return std::tie(nome, marca, preco, revenda, ano) <
               std::tie(outra.nome, outra.marca, outra.preco, outra.revenda, outra.ano);
    }
};

class DataHandler {
public:
    static std::vector<Moto> lerDataset(const std::string& caminho);
};

#endif