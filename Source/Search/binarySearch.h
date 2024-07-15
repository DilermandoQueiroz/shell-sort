#ifndef BINARY_SEARCH_H
#define BINARY_SEARCH_H

#include <vector>
#include "Metrics.h"

// Função para realizar a busca binária
Metrics binarySearch(const std::vector<int>& arr, int target);

// Função para inserir um elemento de forma ordenada em um vetor
Metrics binaryInsert(std::vector<int>& arr, int target);

// Função para remover um elemento de um vetor
Metrics binaryRemove(std::vector<int>& arr, int target);

#endif // BINARYSEARCH_H