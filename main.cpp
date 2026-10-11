// g++ 16.2.0 (MSYS2 UCRT64), build type RELEASE
#include "DatasetManager.h"
#include "Benchmark.h"
#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <filesystem>

using namespace std;

void showMenu() {
    cout << "1. Generate dataset\n";
    cout << "2. Run benchmark\n";
    cout << "3. Exit\n";
    cout << "Enter your choice: ";
}

int main() {

    int choice = 0;
    vector<double> currentDataset;

    while (true) {
        showMenu();
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        if (choice == 1) {
            string filename;
            size_t size;
            cout << "Enter filename (e.g., dataset_1m.txt): ";
            cin >> filename;
            cout << "Enter size (e.g., 1000000): ";
            cin >> size;

            // Create data directory if it doesn't exist
            std::filesystem::create_directory("data");
            string fullPath = "data/" + filename;

            cout << "Generating dataset (" << size << " elements) to " << fullPath << "...\n";
            try {
                DatasetManager::generateDataset(fullPath, size);
                cout << "Dataset generated successfully.\n";
            } catch (const exception& e) {
                cout << "Error: " << e.what() << "\n";
            }
        } else if (choice == 2) {
            string filename;
            cout << "Enter dataset filename to load: ";
            cin >> filename;

            string fullPath = "data/" + filename;

            cout << "Loading dataset from " << fullPath << "...\n";
            try {
                currentDataset = DatasetManager::loadDataset(fullPath);
                cout << "Dataset loaded. Size: " << currentDataset.size() << " elements.\n";
                Benchmark::runAllBenchmarks(currentDataset);
            } catch (const exception& e) {
                cout << "Error: " << e.what() << "\n";
            }
        } else if (choice == 3) {
            cout << "Exiting...\n";
            break;
        } else {
            cout << "Invalid choice. Please select 1, 2, or 3.\n";
        }
    }

    return 0;
}
