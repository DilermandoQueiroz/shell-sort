#ifndef INSERTIONSORT_H
#define INSERTIONSORT_H

#include <vector>
#include "Metrics.h"

// Função para realizar a ordenação usando o Insertion Sort
// Complexidade de tempo no pior caso: O(n^2)
// Complexidade de tempo no melhor caso: O(n)
// Melhor para: pequenas listas quase ordenadas
Metrics insertionSort(std::vector<int>& arr);

#endif // INSERTIONSORT_H
