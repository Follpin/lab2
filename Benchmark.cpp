#include "Benchmark.h"
#include "Operations.h"
#include "ParallelAlgorithms.h"
#include <iostream>
#include <chrono>
#include <execution>
#include <iomanip>
#include <thread>
#include <algorithm>

template <typename Func>
double measureExecutionTime(Func&& func) {
    auto start = std::chrono::high_resolution_clock::now();
    func();
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration = end - start;
    return duration.count();
}

void Benchmark::testFastOperation(const std::vector<double>& inputData) {
    std::vector<double> outputData(inputData.size());
    std::cout << "\nFast Operation (Memory-Bound):\n";

    double timeNoPolicy = measureExecutionTime([&]() {
        std::transform(inputData.begin(), inputData.end(), outputData.begin(), Operations::fastOperation);
    });
    std::cout << std::left << std::setw(30) << "Standard (No Policy):" << timeNoPolicy << " ms\n";

    double timeSeq = measureExecutionTime([&]() {
        std::transform(std::execution::seq, inputData.begin(), inputData.end(), outputData.begin(), Operations::fastOperation);
    });
    std::cout << std::left << std::setw(30) << "Standard (Seq):" << timeSeq << " ms\n";

    double timePar = measureExecutionTime([&]() {
        std::transform(std::execution::par, inputData.begin(), inputData.end(), outputData.begin(), Operations::fastOperation);
    });
    std::cout << std::left << std::setw(30) << "Standard (Par):" << timePar << " ms\n";

    double timeParUnseq = measureExecutionTime([&]() {
        std::transform(std::execution::par_unseq, inputData.begin(), inputData.end(), outputData.begin(), Operations::fastOperation);
    });
    std::cout << std::left << std::setw(30) << "Standard (Par Unseq):" << timeParUnseq << " ms\n";

    int maxThreads = std::thread::hardware_concurrency() * 2;
    if (maxThreads == 0) maxThreads = 8;

    std::cout << "\nCustom Parallel Algorithm (Fast Operation):\n";
    std::cout << std::setw(15) << "Threads (K)" << std::setw(15) << "Time (ms)" << "\n";
    
    double bestTime = -1.0;
    int bestK = -1;

    for (int k = 1; k <= maxThreads; ++k) {
        double timeCustom = measureExecutionTime([&]() {
            customTransform(inputData.begin(), inputData.end(), outputData.begin(), k, Operations::fastOperation);
        });
        std::cout << std::setw(15) << k << std::setw(15) << timeCustom << "\n";
        if (bestTime < 0 || timeCustom < bestTime) {
            bestTime = timeCustom;
            bestK = k;
        }
    }
    
    std::cout << "-> Best K: " << bestK << " (Time: " << bestTime << " ms)\n";
    std::cout << "-> Hardware Threads: " << std::thread::hardware_concurrency() << "\n";
}

void Benchmark::testSlowOperation(const std::vector<double>& inputData) {
    std::vector<double> outputData(inputData.size());
    std::cout << "\nSlow Operation (CPU-Bound):\n";

    double timeNoPolicy = measureExecutionTime([&]() {
        std::transform(inputData.begin(), inputData.end(), outputData.begin(), Operations::slowOperation);
    });
    std::cout << std::left << std::setw(30) << "Standard (No Policy):" << timeNoPolicy << " ms\n";

    double timeSeq = measureExecutionTime([&]() {
        std::transform(std::execution::seq, inputData.begin(), inputData.end(), outputData.begin(), Operations::slowOperation);
    });
    std::cout << std::left << std::setw(30) << "Standard (Seq):" << timeSeq << " ms\n";

    double timePar = measureExecutionTime([&]() {
        std::transform(std::execution::par, inputData.begin(), inputData.end(), outputData.begin(), Operations::slowOperation);
    });
    std::cout << std::left << std::setw(30) << "Standard (Par):" << timePar << " ms\n";

    double timeParUnseq = measureExecutionTime([&]() {
        std::transform(std::execution::par_unseq, inputData.begin(), inputData.end(), outputData.begin(), Operations::slowOperation);
    });
    std::cout << std::left << std::setw(30) << "Standard (Par Unseq):" << timeParUnseq << " ms\n";

    int maxThreads = std::thread::hardware_concurrency() * 2;
    if (maxThreads == 0) maxThreads = 8;

    std::cout << "\nCustom Parallel Algorithm (Slow Operation):\n";
    std::cout << std::setw(15) << "Threads (K)" << std::setw(15) << "Time (ms)" << "\n";
    
    double bestTime = -1.0;
    int bestK = -1;

    for (int k = 1; k <= maxThreads; ++k) {
        double timeCustom = measureExecutionTime([&]() {
            customTransform(inputData.begin(), inputData.end(), outputData.begin(), k, Operations::slowOperation);
        });
        std::cout << std::setw(15) << k << std::setw(15) << timeCustom << "\n";
        if (bestTime < 0 || timeCustom < bestTime) {
            bestTime = timeCustom;
            bestK = k;
        }
    }
    
    std::cout << "-> Best K: " << bestK << " (Time: " << bestTime << " ms)\n";
    std::cout << "-> Hardware Threads: " << std::thread::hardware_concurrency() << "\n";
}

void Benchmark::runAllBenchmarks(const std::vector<double>& inputData) {
    testFastOperation(inputData);
    testSlowOperation(inputData);
}
