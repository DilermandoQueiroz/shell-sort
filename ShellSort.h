#ifndef SHELLSORT_H
#define SHELLSORT_H

#include <vector>
#include "Metrics.h"

// Função para realizar a ordenação usando o Shell Sort
// Complexidade de tempo no pior caso: Depende da sequência de gaps escolhida, mas tipicamente entre O(n^2) e O(n^(3/2))
// Complexidade de tempo no melhor caso: O(n log n)
// Melhor para: listas de tamanho médio a grande com uma boa escolha de gaps
Metrics shellSort(std::vector<int>& arr);

#endif // SHELLSORT_H
