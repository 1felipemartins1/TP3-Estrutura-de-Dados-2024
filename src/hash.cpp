#include "hash.hpp"
#include "funcoes.hpp"
#include <iostream>

bool HashTable::Search(const std::string &s, RechargeStation &result)
{
    int pos = Hash(s);
    int i = 0;

    while (i < tamanhoTabela)
    {
        int newPos = Verifica(pos, i);
        if (tabela[newPos].estado == VAZIO) // Se encontrou uma posição vazia, o item não está na tabela
            return false;

        if (tabela[newPos].estado == OCUPADO && tabela[newPos].endereco->id_end == s)
        {
            result = *(tabela[newPos].endereco);
            return true;
        }
        i++;
    }
    return false;
}
int HashTable::Hash(const std::string &s)
{
    int chave = 0;
    for (int a = 0; a < static_cast<int>(s.size()); a++)
    {
        chave += static_cast<int>(s[a]) * (a + 1);
    }
    return chave % tamanhoTabela;
}

int HashTable::Verifica(int pos, int i)
{
    // Verifica quadrático para reduzir colisões e melhorar performance
    return (pos + i * i) % tamanhoTabela;
}

HashTable::~HashTable()
{
    delete[] tabela; // Desaloca a tabela inteira
}

void HashTable::Insert(const RechargeStation &s)
{
    int pos = Hash(s.id_end);
    int i = 0;

    while (i < tamanhoTabela)
    {
        int newPos = Verifica(pos, i);
        if (tabela[newPos].estado == VAZIO || tabela[newPos].estado == REMOVIDO)
        {
            tabela[newPos].endereco = new RechargeStation(s);
            tabela[newPos].estado = OCUPADO;
            return;
        }
        i++;
    }
    // Tabela cheia, mas sem rehashing, nada pode ser feito
}

HashTable::HashTable(int tamanho)
{
    tabela = new ElementoTabela[tamanho];
    tamanhoTabela = tamanho;
}
