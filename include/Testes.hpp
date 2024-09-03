#ifndef TESTES_HPP
#define TESTES_HPP

#include "hash.hpp"
#include "QuadTree.hpp"
#include "MaxHeap.hpp"
#include <iostream>
#include <cassert>

// Função de teste para a Tabela Hash
void testarTabelaHash() {
    std::cout << "Testando Tabela Hash..." << std::endl;
    HashTable hashTable(10);

    // Dados para teste
    RechargeStation station1 = {"01668501159A", 16685, "RUA", "CONDE DE PALMA", 1159, "Cabana do Pai Tomás", "OESTE", 30512710, 604476.327080534, 7793936.51282176};
    RechargeStation station2 = {"08098800057B", 80988, "RUA", "PEDRO TIMOTHEO", 57, "Vila Vista Alegre", "OESTE", 30514320, 605262.48179415, 7793257.07737953};
    
    // Inserir estações
    hashTable.Insert(station1);
    hashTable.Insert(station2);

    // Pesquisar estações
    RechargeStation result;
    assert(hashTable.Search("01668501159A", result));
    assert(result.id_end == "01668501159A");

    assert(hashTable.Search("08098800057B", result));
    assert(result.id_end == "08098800057B");

    // Testar pesquisa de uma estação não existente
    assert(!hashTable.Search("00000000000C", result));

}

// Função de teste para a Quadtree
void testarQuadtree() {
    std::cout << "Testando Quadtree..." << std::endl;
    QuadTree quadtree(10);

    // Dados para teste
    Point point1(604476.327080534, 7793936.51282176);
    Point point2(605262.48179415, 7793257.07737953);

    // Inserir pontos
    quadtree.insert(point1, "01668501159A");
    quadtree.insert(point2, "08098800057B");

    // Ativar e desativar pontos
    assert(quadtree.activate(point1, "01668501159A"));
    assert(quadtree.deactivate(point1, "01668501159A"));

    // Testar KNN
    Point target(605000.0, 7793500.0);
    Distpair *nearest = quadtree.knn(target, 1);
    assert(nearest != nullptr);
    assert(nearest->id == "08098800057B");

}

// Função de teste para o MaxHeap
void testarMaxHeap() {
    std::cout << "Testando MaxHeap..." << std::endl;
    maxheap<Distpair> maxHeap(10);

    // Dados para teste
    Distpair dp1("01668501159A", 10.0);
    Distpair dp2("08098800057B", 5.0);
    Distpair dp3("02813300418", 15.0);

    // Inserir elementos
    maxHeap.enqueue(dp1);
    maxHeap.enqueue(dp2);
    maxHeap.enqueue(dp3);

    // Testar acesso ao topo
    Distpair top = maxHeap.top();
    assert(top.id == "02813300418");

    // Testar remoção (dequeue)
    Distpair removed = maxHeap.dequeue();
    assert(removed.id == "02813300418");

    // Testar o tamanho do heap
    assert(maxHeap.getSize() == 2);

}

#endif // TESTES_HPP
