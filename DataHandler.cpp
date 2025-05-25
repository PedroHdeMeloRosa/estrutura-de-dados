#include "DataHandler.h"
#include <fstream>
#include <sstream>
#include <stdexcept>

std::vector<Moto> DataHandler::lerDataset(const std::string& caminho) {
    std::vector<Moto> motos;
    std::ifstream arquivo(caminho);
    std::string linha;

    if (!arquivo.is_open()) {
        throw std::runtime_error("Erro ao abrir: " + caminho);
    }

    std::getline(arquivo, linha); // Pular cabeçalho

    while (std::getline(arquivo, linha)) {
        std::stringstream ss(linha);
        Moto moto;
        std::string campo;

        std::getline(ss, campo, ',');
        moto.marca = campo;

        std::getline(ss, campo, ',');
        moto.nome = campo;

        std::getline(ss, campo, ',');
        moto.preco = std::stod(campo);

        std::getline(ss, campo, ',');
        moto.revenda = std::stod(campo);

        std::getline(ss, campo, ',');
        moto.ano = std::stoi(campo);

        motos.push_back(moto);
    }

    return motos;
}