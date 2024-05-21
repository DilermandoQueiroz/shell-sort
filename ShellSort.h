#ifndef SHELLSORT_H
#define SHELLSORT_H

#include <vector>

// Função para realizar a ordenação usando o Shell Sort
// Complexidade de tempo no pior caso: Depende da sequência de gaps utilizada (geralmente entre O(n^2) e O(n log^2 n))
// Complexidade de tempo no melhor caso: O(n log n)
// Melhor para: listas de tamanho médio a grande onde a estabilidade não é uma preocupação
void shellSort(std::vector<int>& arr);

#endif // SHELLSORT_H
