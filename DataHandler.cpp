//
// Created by Pedro on 24/05/2025.
//

#include "DataHandler.h"
#include <fstream>
#include <sstream>
#include <stdexcept>

std::vector<Moto> DataHandler::lerDataset(const std::string& caminho) {
    std::vector<Moto> motos;
    std::ifstream arquivo(caminho);
    std::string linha;

    if (!arquivo.is_open()) {
        throw std::runtime_error("Erro ao abrir o arquivo!");
    }

    // Pular cabeçalho
    std::getline(arquivo, linha);

    while (std::getline(arquivo, linha)) {
        std::stringstream ss(linha);
        Moto moto;
        std::string campo;

        // Extrair marca e modelo (exemplo: "Hero Splendor")
        std::getline(ss, campo, ',');
        size_t pos = campo.find(' ');
        if (pos != std::string::npos) {
            moto.marca = campo.substr(0, pos);
            moto.modelo = campo.substr(pos + 1);
        }

        // Preço
        std::getline(ss, campo, ',');
        moto.preco = std::stod(campo);

        // Pular colunas não usadas (ex: km_driven)
        for (int i = 0; i < 3; i++) std::getline(ss, campo, ',');

        // Preço de revenda
        std::getline(ss, campo, ',');
        moto.preco_revenda = std::stod(campo);

        // Ano
        std::getline(ss, campo, ',');
        moto.ano = std::stoi(campo);

        motos.push_back(moto);
    }

    return motos;
}