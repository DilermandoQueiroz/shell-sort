#ifndef SELECTIONSORT_H
#define SELECTIONSORT_H

#include <vector>
#include "Metrics.h"

// Função para realizar a ordenação usando o Selection Sort
// Complexidade de tempo no pior caso: O(n^2)
// Complexidade de tempo no melhor caso: O(n^2)
// Melhor para: listas pequenas onde a estabilidade não é uma preocupação
Metrics selectionSort(std::vector<int>& arr);

#endif // SELECTIONSORT_H
