#include "BinarySearch.h"
#include <algorithm>
#include <chrono>

Metrics binarySearch(const std::vector<int>& arr, int target) {
    Metrics metrics;
    auto start = std::chrono::high_resolution_clock::now();

    int left = 0, right = arr.size() - 1;
    while (left <= right) {
        metrics.comparisons++;
        int mid = left + (right - left) / 2;
        if (arr[mid] == target) {
            break;
        } else if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    metrics.time_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    return metrics;
}

Metrics binaryInsert(std::vector<int>& arr, int value) {
    Metrics metrics;
    auto start = std::chrono::high_resolution_clock::now();

    arr.push_back(value);
    std::sort(arr.begin(), arr.end());
    metrics.movements += arr.size();  // Approximate movements

    auto end = std::chrono::high_resolution_clock::now();
    metrics.time_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    return metrics;
}

Metrics binaryRemove(std::vector<int>& arr, int value) {
    Metrics metrics;
    auto start = std::chrono::high_resolution_clock::now();

    auto it = std::lower_bound(arr.begin(), arr.end(), value);
    if (it != arr.end() && *it == value) {
        arr.erase(it);
        metrics.movements++;
    }

    auto end = std::chrono::high_resolution_clock::now();
    metrics.time_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    return metrics;
}
