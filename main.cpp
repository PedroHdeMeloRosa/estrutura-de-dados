#include <iostream>
#include <limits>
#include <string>
#include "DataHandler.h"
#include "LinkedList.h"
#include "AVLTree.h"
#include "HashTable.h"
#include "BloomFilter.h"
#include "RadixTree.h"

template <typename NumType>
NumType validarNumero(const std::string& prompt) {
    NumType valor;
    while (true) {
        std::cout << prompt;
        if (std::cin >> valor) break;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Erro: Valor inválido! Tente novamente.\n";
    }
    return valor;
}

void limparBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

template <typename T>
void menuEstrutura(T& estrutura, const std::string& nomeEstrutura) {
    int escolha;
    int passosDummy = 0;

    auto obterDadosMoto = [](bool busca = false) -> Moto {
        Moto moto;
        std::cout << "Marca: ";
        std::getline(std::cin, moto.marca);
        std::cout << "Modelo: ";
        std::getline(std::cin, moto.nome);

        if (!busca) {
            moto.preco = validarNumero<float>("Preço: ");
            moto.revenda = validarNumero<float>("Revenda: ");
            moto.ano = validarNumero<int>("Ano: ");
            limparBuffer();
        }
        return moto;
    };

    do {
        std::cout << "\n=== MENU " << nomeEstrutura << " ===\n"
                  << "1. Inserir Moto\n"
                  << "2. Remover Moto\n"
                  << "3. Buscar Moto\n"
                  << "4. Exibir Todas\n"
                  << "0. Voltar\n"
                  << "Escolha: ";

        if (!(std::cin >> escolha)) {
            std::cout << "\nErro: Entrada inválida!\n";
            limparBuffer();
            continue;
        }
        limparBuffer();

        try {
            switch (escolha) {
                case 1: {
                    Moto novaMoto = obterDadosMoto();
                    if constexpr (std::is_same_v<T, RadixTree<Moto>>) {
                        if (estrutura.buscar(novaMoto, passosDummy)) {
                            std::cout << "\nErro: Moto já existe!\n";
                        } else {
                            estrutura.inserir(novaMoto);
                            std::cout << "\nInserção bem sucedida!\n";
                        }
                    } else {
                        estrutura.inserir(novaMoto);
                        std::cout << "\nOperação realizada!\n";
                    }
                    break;
                }

                case 2: {
                    if constexpr (std::is_same_v<T, BloomFilter<Moto>> ||
                                 std::is_same_v<T, RadixTree<Moto>>) {
                        std::cout << "\nErro: Operação não suportada!\n";
                                 } else {
                                     Moto moto = obterDadosMoto(true);
                                     if (estrutura.remover(moto)) {
                                         std::cout << "\nRemoção realizada! (Todos os itens correspondentes)\n";
                                     } else {
                                         std::cout << "\nNenhuma moto encontrada com esses critérios!\n";
                                     }
                                 }
                    break;
                }

                case 3: {
                    auto obterDadosMoto = [](bool busca = false) -> Moto {
                        Moto moto;
                        std::cout << "Marca (deixe vazio para qualquer): ";
                        std::getline(std::cin, moto.marca);
                        std::cout << "Modelo (deixe vazio para qualquer): ";
                        std::getline(std::cin, moto.nome);

                        std::cout << "Preço (-1 para qualquer): ";
                        moto.preco = validarNumero<float>("");
                        std::cout << "Revenda (-1 para qualquer): ";
                        moto.revenda = validarNumero<float>("");
                        std::cout << "Ano (-1 para qualquer): ";
                        moto.ano = validarNumero<int>("");

                        limparBuffer();
                        return moto;
                    };
                    break;
                }

                case 4: {
                    if constexpr (std::is_same_v<T, BloomFilter<Moto>>) {
                        estrutura.exibir();
                    } else {
                        estrutura.exibir();
                    }
                    break;
                }

                case 0: break;
                default: std::cout << "\nOpção inválida!\n";
            }
        } catch (const std::exception& e) {
            std::cerr << "\nErro: " << e.what() << "\n";
        }
    } while (escolha != 0);
}

int main() {
    try {
        LinkedList<Moto> lista;
        AVLTree<Moto> arvore;
        HashTable<Moto> tabelaHash;
        BloomFilter<Moto> bloomFilter;
        RadixTree<Moto> radixTree;

        auto motos = DataHandler::lerDataset("../data/bike_sales_india.csv");
        for (const auto& moto : motos) {
            lista.inserir(moto);
            arvore.inserir(moto);
            tabelaHash.inserir(moto);
            bloomFilter.inserir(moto);
            radixTree.inserir(moto);
        }

        int escolha;
        do {
            std::cout << "\n=== MENU PRINCIPAL ===\n"
                      << "1. Lista Encadeada\n"
                      << "2. Árvore AVL\n"
                      << "3. Tabela Hash\n"
                      << "4. Bloom Filter\n"
                      << "5. Radix Tree\n"
                      << "0. Sair\n"
                      << "Escolha: ";

            if (!(std::cin >> escolha)) {
                std::cout << "\nEntrada inválida!\n";
                limparBuffer();
                continue;
            }
            limparBuffer();

            switch (escolha) {
                case 1: menuEstrutura(lista, "LISTA ENCADEADA"); break;
                case 2: menuEstrutura(arvore, "ÁRVORE AVL"); break;
                case 3: menuEstrutura(tabelaHash, "TABELA HASH"); break;
                case 4: menuEstrutura(bloomFilter, "BLOOM FILTER"); break;
                case 5: menuEstrutura(radixTree, "RADIX TREE"); break;
                case 0: std::cout << "\nEncerrando...\n"; break;
                default: std::cout << "\nOpção inválida!\n";
            }
        } while (escolha != 0);

    } catch (const std::exception& e) {
        std::cerr << "\nERRO: " << e.what() << "\n";
        return 1;
    }
    return 0;
}