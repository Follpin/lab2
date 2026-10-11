#include "Operations.h"
#include <cmath>

double Operations::fastOperation(double value) {
    return value * 2.5 + 3.14;
}

double Operations::slowOperation(double value) {
    double result = value;
    for (int i = 0; i < 200; ++i) {
        result = std::sin(result) * std::cos(result) + std::sqrt(std::abs(result));
    }
    return result;
}
