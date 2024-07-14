#include "LinearSearch.h"
#include "Metrics.h"
#include <vector>
#include <chrono>  
#include <algorithm>  
#include <iostream>

// Implementação da função de busca linear (exemplo)
Metrics linearSearch(const std::vector<int>& arr, int target) {
    Metrics metrics;
    auto start = std::chrono::high_resolution_clock::now();

    std::cerr << "Iniciando linearSearch em vetor de tamanho " << arr.size() << std::endl;
    for (size_t i = 0; i < arr.size(); ++i) {
        metrics.comparisons++;
        if (arr[i] == target) {
            break;
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    metrics.time_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    return metrics;
}

Metrics linearInsert(std::vector<int>& arr, int value) {
    Metrics metrics;
    auto start = std::chrono::high_resolution_clock::now();

    std::cerr << "Inserindo valor " << value << " em vetor de tamanho " << arr.size() << std::endl;
    
    // Limite de tamanho para evitar crescimento descontrolado
    if (arr.size() > 1000000) {
        std::cerr << "Tamanho do vetor excedeu o limite permitido. Abortando inserção." << std::endl;
        return metrics;
    }

    arr.push_back(value);
    metrics.movements++;  // Contabiliza a inserção do elemento

    auto end = std::chrono::high_resolution_clock::now();
    metrics.time_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    return metrics;
}


// Implementação da função de remoção linear (exemplo)
Metrics linearRemove(std::vector<int>& arr, int value) {
    Metrics metrics;
    auto start = std::chrono::high_resolution_clock::now();

    std::cerr << "Removendo valor " << value << " de vetor de tamanho " << arr.size() << std::endl;
    auto it = std::find(arr.begin(), arr.end(), value);
    if (it != arr.end()) {
        arr.erase(it);
        metrics.movements++;  // Contabiliza a remoção do elemento
    }

    auto end = std::chrono::high_resolution_clock::now();
    metrics.time_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    return metrics;
}
