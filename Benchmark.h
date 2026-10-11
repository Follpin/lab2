#pragma once
#include <vector>

class Benchmark {
public:
    static void runAllBenchmarks(const std::vector<double>& inputData);
    
private:
    static void testFastOperation(const std::vector<double>& inputData);
    static void testSlowOperation(const std::vector<double>& inputData);
};
