#include <iostream>
#include "DataHandler.h"
#include "LinkedList.h"

void menuListaEncadeada(LinkedList<Moto>& lista) {
    int escolha;
    do {
        std::cout << "\n=== MENU LISTA ENCADEADA ===\n";
        std::cout << "1. Inserir Moto\n";
        std::cout << "2. Buscar Moto\n";
        std::cout << "3. Exibir Todas\n";
        std::cout << "0. Voltar\n";
        std::cout << "Escolha: ";
        std::cin >> escolha;

        if (escolha == 1) {
            Moto moto;
            std::cout << "Modelo: ";
            std::cin >> moto.modelo;
            std::cout << "Preço: ";
            std::cin >> moto.preco;
            lista.inserir(moto);
        } else if (escolha == 2) {
            Moto moto;
            std::cout << "Modelo a buscar: ";
            std::cin >> moto.modelo;
            std::cout << (lista.buscar(moto) ? "Encontrado!" : "Não encontrado!") << std::endl;
        } else if (escolha == 3) {
            lista.exibir();
        }
    } while (escolha != 0);
}

int main() {
    auto motos = DataHandler::lerDataset("../data/bike_sales_india.csv"); // Caminho relativo
    LinkedList<Moto> lista;

    // Inserir dados do dataset na lista
    for (const auto& moto : motos) {
        lista.inserir(moto);
    }

    menuListaEncadeada(lista);
    return 0;
}