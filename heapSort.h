#ifndef HEAPSORT_H
#define HEAPSORT_H

#include <vector>

// Função para realizar a ordenação usando o Heap Sort
// Complexidade de tempo no pior caso: O(n log n)
// Complexidade de tempo no melhor caso: O(n log n)
// Melhor para: listas grandes onde a complexidade O(n log n) é desejada
void heapSort(std::vector<int>& arr);

#endif // HEAPSORT_H
