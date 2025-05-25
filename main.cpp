#include <iostream>
#include <limits>
#include "DataHandler.h"
#include "LinkedList.h"

void menuListaEncadeada(LinkedList<Moto>& lista) {
    int escolha;
    do {
        std::cout << "\n=== MENU LISTA ENCADEADA ===\n"
                  << "1. Inserir Moto\n"
                  << "2. Buscar Moto Exata\n"  // Opção renomeada
                  << "3. Exibir Todas\n"
                  << "0. Voltar\n"
                  << "Escolha: ";
        std::cin >> escolha;
        std::cin.ignore();

        if (escolha == 1) {
            Moto moto;
            std::cout << "Marca: ";
            std::getline(std::cin, moto.marca);
            std::cout << "Modelo: ";
            std::getline(std::cin, moto.nome);
            std::cout << "Preço: ";
            std::cin >> moto.preco;
            std::cout << "Revenda: ";
            std::cin >> moto.revenda;
            std::cout << "Ano: ";
            std::cin >> moto.ano;
            lista.inserir(moto);
            std::cin.ignore();

        } else if (escolha == 2) {
            Moto alvo;
            std::cout << "Digite todos os dados da moto:\n";
            std::cout << "Marca: ";
            std::getline(std::cin, alvo.marca);
            std::cout << "Modelo: ";
            std::getline(std::cin, alvo.nome);
            std::cout << "Preço: ";
            std::cin >> alvo.preco;
            std::cout << "Revenda: ";
            std::cin >> alvo.revenda;
            std::cout << "Ano: ";
            std::cin >> alvo.ano;

            int pos = lista.buscarExato(alvo);
            if (pos != -1) {
                std::cout << "\n✅ Moto encontrada na posição: " << pos << "\n";
            } else {
                std::cout << "\n❌ Moto não encontrada!\n";
            }

        } else if (escolha == 3) {
            lista.exibir();
        }
    } while (escolha != 0);
}

int main() {
    try {
        LinkedList<Moto> lista;
        auto motos = DataHandler::lerDataset("../data/bike_sales_india.csv");

        for (const auto& moto : motos) {
            lista.inserir(moto);
        }

        menuListaEncadeada(lista);
    } catch (const std::exception& e) {
        std::cerr << "Erro: " << e.what() << "\n";
        return 1;
    }
    return 0;
}