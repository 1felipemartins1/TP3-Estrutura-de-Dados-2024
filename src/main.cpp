#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstring> // Necessário para usar strcpy
#include "QuadTree.hpp"
#include "funcoes.hpp"
#include "Operadores.hpp"
#include "MaxHeap.hpp"
#include "hash.hpp"
#include "quicksort.hpp"
#include "Testes.hpp"
using namespace std;

int countPointsInArea(PointID *stations, int l, int r, double minX, double minY, double maxX, double maxY)
{
    int count = 0;
    for (int i = l; i <= r; i++)
    {
        if (stations[i].p.cordx >= minX && stations[i].p.cordx <= maxX &&
            stations[i].p.cordy >= minY && stations[i].p.cordy <= maxY)
        {
            count++;
        }
    }
    return count;
}

void reversePoints(PointID *stations, int l, int r)
{
    while (l < r)
    {
        PointID temp = stations[l];
        stations[l] = stations[r];
        stations[r] = temp;
        l++;
        r--;
    }
}

void QuickSortInsere(PointID *stations, QuadTree &quadtree, int l, int r)
{
    if (l > r)
    {
        return;
    }

    int mid = l + (r - l) / 2;
    quadtree.insert({stations[mid].p.cordx, stations[mid].p.cordy}, stations[mid].id);

    QuickSortInsere(stations, quadtree, l, mid - 1);
    QuickSortInsere(stations, quadtree, mid + 1, r);
}

void InsereQuadTree(PointID *Stations, QuadTree &quadtree, int l, int r)
{
    MedianInsQuickSort(Stations, l, r);
    QuickSortInsere(Stations, quadtree, l, r);
}

int main(int argc, char *argv[])
{
    if (argc != 5)
    {
        cerr << "Uso: " << argv[0] << " -b <arquivo_base> -e <arquivo_eventos>" << endl;
        return -1;
    }

    string caminhoArquivoBase;
    string caminhoArquivoEventos;

    for (int i = 1; i < argc; i += 2)
    {
        string argumento = argv[i];
        if (argumento == "-b")
        {
            caminhoArquivoBase = argv[i + 1];
        }
        else if (argumento == "-e")
        {
            caminhoArquivoEventos = argv[i + 1];
        }
        else
        {
            cerr << "Parâmetro desconhecido: " << argumento << endl;
            return -1;
        }
    }

    // Inicializa com precisão 3 casas decimais
    cout << fixed;

    ifstream arquivoEstacoes(caminhoArquivoBase);

    if (!arquivoEstacoes.is_open())
    {
        cerr << "Erro ao abrir o arquivo de base: " << caminhoArquivoBase << endl;
        return -1;
    }

    string linhaCabecalho;
    getline(arquivoEstacoes, linhaCabecalho, '\n');
    int quantidadeEstacoes = stoi(linhaCabecalho);
    
    // Ajusta o tamanho da tabela hash e da quadtree de acordo com quantidadeEstacoes
    HashTable tabelaEstacoes(static_cast<int>(1.4 * quantidadeEstacoes));
    QuadTree quadtree(quantidadeEstacoes);
    PointID *vetorEstacoes = new PointID[quantidadeEstacoes];

    string linha;
    for (int i = 0; i < quantidadeEstacoes; i++)
    {
        RechargeStation dadosEstacao;
        getline(arquivoEstacoes, linha);

        stringstream streamLinha(linha);
        string stringTemporaria;

        getline(streamLinha, dadosEstacao.id_end, ';');
        getline(streamLinha, stringTemporaria, ';');
        dadosEstacao.id_lograd = stol(stringTemporaria);
        getline(streamLinha, dadosEstacao.sigla_tipo, ';');
        getline(streamLinha, dadosEstacao.nome_lograd, ';');
        getline(streamLinha, stringTemporaria, ';');
        dadosEstacao.imovel = stoi(stringTemporaria);
        getline(streamLinha, dadosEstacao.nome_bairro, ';');
        getline(streamLinha, dadosEstacao.nome_regiao, ';');
        getline(streamLinha, stringTemporaria, ';');
        dadosEstacao.cep = stoi(stringTemporaria);
        getline(streamLinha, stringTemporaria, ';');
        dadosEstacao.x = stod(stringTemporaria);
        getline(streamLinha, stringTemporaria, ';');
        dadosEstacao.y = stod(stringTemporaria);

        tabelaEstacoes.Insert(dadosEstacao);
        vetorEstacoes[i] = {dadosEstacao.id_end, {dadosEstacao.x, dadosEstacao.y}};
    }

    arquivoEstacoes.close();

    InsereQuadTree(vetorEstacoes, quadtree, 0, quantidadeEstacoes - 1);

    delete[] vetorEstacoes;

    ifstream arquivoConsultas(caminhoArquivoEventos);
    if (!arquivoConsultas.is_open())
    {
        cerr << "Erro" << caminhoArquivoEventos << endl;
        return -1;
    }

    getline(arquivoConsultas, linhaCabecalho);
    int quantidadeConsultas = stoi(linhaCabecalho);
    quantidadeConsultas = quantidadeConsultas + 10;
    for (int i = 0; i < quantidadeConsultas; i++)
    {
        getline(arquivoConsultas, linha);
        stringstream streamLinha(linha);
        string acao, id, stringTemporaria;
        double coordenadaX, coordenadaY;
        int numeroPontos;

        getline(streamLinha, acao, ' ');

        if (acao == "C")
        {
            cout << acao << " ";
            cout << fixed << setprecision(6);

            getline(streamLinha, stringTemporaria, ' ');
            coordenadaX = stod(stringTemporaria);
            getline(streamLinha, stringTemporaria, ' ');
            coordenadaY = stod(stringTemporaria);
            getline(streamLinha, stringTemporaria, ' ');
            numeroPontos = stoi(stringTemporaria);
            Point pontoConsulta = {coordenadaX, coordenadaY};

            cout << coordenadaX << " " << coordenadaY << " " << numeroPontos << endl;

            Distpair *vizinhosMaisProximos = quadtree.knn(pontoConsulta, numeroPontos);

            for (int i = 0; i < numeroPontos; i++)
            {
                RechargeStation dadosEstacao;
                tabelaEstacoes.Search(vizinhosMaisProximos[i].id, dadosEstacao);

                cout << fixed << setprecision(3);
                cout << dadosEstacao.sigla_tipo << ' ' << dadosEstacao.nome_lograd << ", " << dadosEstacao.imovel << ", "
                     << dadosEstacao.nome_bairro << ", " << dadosEstacao.nome_regiao << ", " << dadosEstacao.cep
                     << " (" << vizinhosMaisProximos[i].distancia << ")" << endl;

                cout << fixed << setprecision(6);
            }
        }
        else
        {
            cout << fixed << setprecision(3);
            cout << acao << " ";

            if (acao == "A" || acao == "D")
            {
                getline(streamLinha, id, ' ');
                cout << id << endl;
                RechargeStation dadosEstacao;
                tabelaEstacoes.Search(id, dadosEstacao);

                if (acao == "A")
                {
                    if (quadtree.activate({dadosEstacao.x, dadosEstacao.y}, id))
                    {
                        cout << "Ponto de recarga " << id << " ativado." << endl;
                    }
                    else
                    {
                        cout << "Ponto de recarga " << id << " já estava ativo." << endl;
                    }
                }
                else if (acao == "D")
                {
                    if (quadtree.deactivate({dadosEstacao.x, dadosEstacao.y}, id))
                    {
                        cout << "Ponto de recarga " << id << " desativado." << endl;
                    }
                    else
                    {
                        cout << "Ponto de recarga " << id << " já estava desativado." << endl;
                    }
                }
            }
        }
    }

    arquivoConsultas.close();

    return 0;
}
