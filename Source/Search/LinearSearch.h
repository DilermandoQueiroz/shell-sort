#ifndef LINEARSEARCH_H
#define LINEARSEARCH_H

#include <vector>
#include "Metrics.h"

// Função para realizar a busca linear
Metrics linearSearch(const std::vector<int>& arr, int target);

// Função para inserir um elemento em um vetor (sem ordenação)
Metrics linearInsert(std::vector<int>& arr, int target);

// Função para remover um elemento de um vetor
Metrics linearRemove(std::vector<int>& arr, int target);

#endif // LINEARSEARCH_H