# BiUaiDi Charging Stations - App Modernization

## Descrição do Projeto

Este projeto é uma modernização do aplicativo de identificação de estações de recarga da BiUaiDi, uma fabricante de carros elétricos. O aplicativo é utilizado para localizar as estações de recarga mais próximas da posição atual do veículo em Belo Horizonte. A versão anterior do aplicativo possuía limitações em termos de eficiência, especialmente ao lidar com grandes quantidades de dados e operações dinâmicas, como ativação/desativação de estações.

### O Problema

Carros elétricos dependem de estações de recarga distribuídas pela cidade para manter suas baterias carregadas. Para otimizar a experiência do usuário, é crucial que o sistema de navegação do veículo possa identificar rapidamente as estações mais próximas da sua localização atual. No entanto, quando o número de estações cresce, o algoritmo simples de busca sequencial se torna ineficiente, especialmente se o veículo se move rapidamente ou se as estações podem ser ativadas e desativadas frequentemente.

### O Programa

O programa desenvolvido neste projeto resolve o problema de forma eficiente utilizando uma estrutura de dados conhecida como `QuadTree`. Esta estrutura é particularmente adequada para armazenar e consultar dados geográficos, como coordenadas de latitude e longitude.

#### Funcionalidades Principais:

1. **Inserção de Estações de Recarga:** O programa permite que as coordenadas das estações de recarga sejam armazenadas em uma `QuadTree`, o que facilita a organização espacial dos dados.

2. **Busca por Estações Mais Próximas:** Dada uma coordenada `(x, y)` que representa a localização atual do veículo, o programa é capaz de identificar as `X` estações de recarga mais próximas com base na distância euclidiana.

3. **Ativação/Desativação Dinâmica:** O programa suporta a ativação e desativação de estações de recarga em tempo real. Esta funcionalidade é essencial para lidar com situações em que algumas estações possam estar temporariamente fora de serviço ou quando novas estações são adicionadas ao sistema.

4. **Eficiência e Escalabilidade:** Utilizando a `QuadTree`, o programa pode realizar buscas e atualizações de forma mais eficiente do que métodos tradicionais de busca linear, especialmente em cenários com um grande número de estações distribuídas em uma área extensa.

### Avaliação Experimental

O projeto inclui uma avaliação comparativa entre a versão original e a versão modernizada do aplicativo, focando em:
- **Desempenho:** Comparação do tempo de execução para operações de inserção, busca e atualização.
- **Uso de Memória:** Análise da eficiência em termos de localidade de referência e acesso à memória.
- **Escalabilidade:** Testes com diferentes números de estações de recarga e padrões de movimentação do veículo.

## Requisitos

- **Linguagem de Programação:** C/C++
- **Estruturas de Dados:** QuadTree
- **Bibliotecas:** I/O padrão de C++ (`<iostream>`, `<fstream>`, `<sstream>`)

## Como Usar

1. **Compilar o Projeto:**
   Compile os arquivos fonte usando um compilador C++:
   ```bash
   make all
