#ifndef BUBBLESORT_H
#define BUBBLESORT_H

#include <vector>
#include "Metrics.h"

// Função para realizar a ordenação usando o Bubble Sort
// Complexidade de tempo no pior caso: O(n^2)
// Complexidade de tempo no melhor caso: O(n)
// Melhor para: listas pequenas ou quando se deseja uma implementação simples
Metrics bubbleSort(std::vector<int>& arr);

#endif // BUBBLESORT_H
