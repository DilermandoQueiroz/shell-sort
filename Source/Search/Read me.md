# Projeto de Análise de Algoritmos de Busca e Árvores

Este projeto tem como objetivo analisar o desempenho de diferentes algoritmos de busca e estruturas de dados de árvore (AVL, Red-Black, etc.) em diferentes tipos de arranjos (ordenados, reversos, quase ordenados e aleatórios).

## Algoritmos Implementados

### Algoritmos de Busca
- Linear Search

### Estruturas de Dados de Árvores
- AVL Tree

## Como Compilar e Executar

### Pré-requisitos

- Compilador C++ (g++)
- Git
- Git Bash (ou qualquer terminal compatível)

### Passo a Passo

1. **Clone o repositório:**
    ```bash
    git clone <URL-do-repositório>
    cd <nome-do-repositório>
    ```

2. **Compile o projeto:**
    ```bash
    g++ -o main main.cpp LinearSearch.cpp AVLTree.cpp FingerTree.cpp binarySearch.cpp binarySearchTree.cpp
    ```

3. **Execute o programa:**
    ```bash
    ./main
    ```

4. **Verifique os resultados:**
    O programa irá gerar um arquivo `search_results.csv` com as métricas de desempenho para cada algoritmo testado.

## Estrutura de Arquivos

- `main.cpp`: Arquivo principal que executa os testes.
- `LinearSearch.cpp`: Implementação do algoritmo de busca linear.
- `AVLTree.cpp`: Implementação da árvore AVL.
- `Metrics.h`: Definição da estrutura `Metrics` para coleta de métricas.
- `search_results.csv`: Arquivo de saída gerado após a execução do programa contendo as métricas coletadas.

## Funcionalidades Implementadas até Agora

- **Algoritmos de Busca:**
  - Linear Search: Implementado e funcional.

- **Estruturas de Dados de Árvores:**
  - AVL Tree: Implementado e funcional.

## Próximos Passos

- Implementar e testar os algoritmos de busca binária.
- Implementar e testar as árvores de busca binária e Red-Black.

## Contribuições

Sinta-se à vontade para contribuir com o projeto abrindo issues ou enviando pull requests.

## Licença

Este projeto está licenciado sob a MIT License. Consulte o arquivo `LICENSE` para obter mais informações.
