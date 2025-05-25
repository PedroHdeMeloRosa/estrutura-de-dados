#include <iostream>
#include <limits>
#include "DataHandler.h"
#include "LinkedList.h"
#include "AVLTree.h"
#include "HashTable.h"
#include "CuckooHashTable.h"

template <typename T>
void menuEstrutura(T& estrutura, const std::string& nomeEstrutura) {
    int escolha;
    do {
        std::cout << "\n=== MENU " << nomeEstrutura << " ===\n"
                  << "1. Inserir Moto\n"
                  << "2. Remover Moto\n"
                  << "3. Buscar Moto Exata\n"
                  << "4. Exibir Todas\n"
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
            estrutura.inserir(moto);
            std::cin.ignore();

        } else if (escolha == 2) {
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
            if constexpr (std::is_same_v<T, LinkedList<Moto>>) {
                estrutura.remover(moto);
            } else {
                std::cout << "Remoção não suportada nesta estrutura!\n";
            }
            std::cin.ignore();

        } else if (escolha == 3) {
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

            int passos = 0;
            bool encontrado = estrutura.buscar(moto, passos);

            std::cout << (encontrado ? "Encontrado" : "Não encontrado")
                      << " | Passos: " << passos << "\n";
            std::cin.ignore();

        } else if (escolha == 4) {
            estrutura.exibir();
        }
    } while (escolha != 0);
}

int main() {
    try {
        LinkedList<Moto> lista;
        AVLTree<Moto> arvore;
        HashTable<Moto> tabelaHash;
        CuckooHashTable<Moto> cuckooHash;
        auto motos = DataHandler::lerDataset("../data/bike_sales_india.csv");

        for (const auto& moto : motos) {
            lista.inserir(moto);
            arvore.inserir(moto);
            tabelaHash.inserir(moto);
            cuckooHash.inserir(moto);
        }

        int escolha;
        do {
            std::cout << "\n=== MENU PRINCIPAL ===\n"
                      << "1. Lista Encadeada\n"
                      << "2. Arvore AVL\n"
                      << "3. Tabela Hash\n"
                      << "4. Cuckoo Hashing\n"
                      << "0. Sair\n"
                      << "Escolha: ";
            std::cin >> escolha;
            std::cin.ignore();

            if (escolha == 1) menuEstrutura(lista, "LISTA ENCADEADA");
            else if (escolha == 2) menuEstrutura(arvore, "ÁRVORE AVL");
            else if (escolha == 3) menuEstrutura(tabelaHash, "TABELA HASH");
            else if (escolha == 4) menuEstrutura(cuckooHash, "CUCKOO HASHING");

        } while (escolha != 0);

    } catch (const std::exception& e) {
        std::cerr << "Erro: " << e.what() << "\n";
        return 1;
    }
    return 0;
}