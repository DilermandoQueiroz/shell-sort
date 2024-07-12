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
};

#endif // METRICS_H
