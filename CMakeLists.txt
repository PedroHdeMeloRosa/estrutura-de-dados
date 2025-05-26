cmake_minimum_required(VERSION 3.30)
project(Estrutura_de_Dados)

set(CMAKE_CXX_STANDARD 20)

add_executable(Estrutura_de_Dados main.cpp
        DataHandler.h
        DataHandler.cpp
        LinkedList.h
        AVLTree.h
        HashTable.h
        BloomFilter.h
        RadixTree.h
)
