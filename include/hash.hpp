#ifndef HASH_HPP
#define HASH_HPP

#include "funcoes.hpp"
#include <string>

enum Estado
{
    VAZIO,
    OCUPADO,
    REMOVIDO
};

struct ElementoTabela
{
    RechargeStation *endereco; // Ponteiro para economizar memória
    Estado estado;

    ElementoTabela() : endereco(nullptr), estado(VAZIO) {}
    ~ElementoTabela() { delete endereco; } // Desaloca o ponteiro
};

class HashTable
{
public:
    HashTable(int tamanho = 100);
    ~HashTable();
    bool Search(const std::string &s, RechargeStation &result);
    void Insert(const RechargeStation &s);
    int tamanhoTabela;
    ElementoTabela *tabela;

    int Hash(const std::string &s);
    int Verifica(int pos, int i);
};

#endif // HASH_HPP
