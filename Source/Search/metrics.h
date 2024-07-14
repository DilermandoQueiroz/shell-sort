#ifndef METRICS_H
#define METRICS_H

#include <string>

struct Metrics {
    std::string algorithm;
    std::string arrayType;
    int size;
    long long comparisons;
    long long movements;
    double time_us;

    Metrics() : algorithm(""), arrayType(""), size(0), comparisons(0), movements(0), time_us(0.0) {}
    Metrics(const std::string& algo, const std::string& arrType, int sz, long long comp, long long mov, double time)
        : algorithm(algo), arrayType(arrType), size(sz), comparisons(comp), movements(mov), time_us(time) {}
};

#endif // METRICS_H
