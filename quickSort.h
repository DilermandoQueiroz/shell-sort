#ifndef QUICKSORT_H
#define QUICKSORT_H

#include <vector>
#include "Metrics.h"

// Função para realizar a ordenação usando o Quick Sort
// Complexidade de tempo no pior caso: O(n^2)
// Complexidade de tempo no melhor caso: O(n log n)
// Melhor para: listas grandes onde a estabilidade não é uma preocupação
Metrics quickSort(std::vector<int>& arr);

#endif // QUICKSORT_H
