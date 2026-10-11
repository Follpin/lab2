#pragma once
#include <string>
#include <vector>
#include <cstddef>

class DatasetManager {
public:
    static void generateDataset(const std::string& filename, std::size_t size);
    static std::vector<double> loadDataset(const std::string& filename);
};
