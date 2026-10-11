#include "DatasetManager.h"
#include <fstream>
#include <random>
#include <stdexcept>

void DatasetManager::generateDataset(const std::string& filename, std::size_t size) {
    std::ofstream outFile(filename);
    if (!outFile.is_open()) {
        throw std::runtime_error("Couldn't open file for writing: " + filename);
    }
    
    // Seed with random_device for better randomness, though fixed seed is fine for repeatable benchmarks
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_real_distribution<double> distribution(1.0, 100.0);

    for (std::size_t i = 0; i < size; ++i) {
        outFile << distribution(generator) << "\n";
    }
}

std::vector<double> DatasetManager::loadDataset(const std::string& filename) {
    std::ifstream inFile(filename);
    if (!inFile.is_open()) {
        throw std::runtime_error("Couldn't open file for reading: " + filename);
    }
    
    std::vector<double> data;
    // Reserve capacity if we can guess, but here we just read stream
    double value;
    while (inFile >> value) {
        data.push_back(value);
    }
    return data;
}
