#ifndef MERGESORT_H
#define MERGESORT_H

#include <vector>

// Função para realizar a ordenação usando o Merge Sort
// Complexidade de tempo no pior caso: O(n log n)
// Complexidade de tempo no melhor caso: O(n log n)
// Melhor para: listas grandes onde a estabilidade é importante
void mergeSort(std::vector<int>& arr);

#endif // MERGESORT_H
