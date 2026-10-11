#pragma once
#include <vector>
#include <thread>
#include <algorithm>
#include <iterator>

template <typename InputIt, typename OutputIt, typename UnaryOperation>
void customTransform(InputIt first, InputIt last, OutputIt dFirst, int k, UnaryOperation policy) {
    auto size = std::distance(first, last);
    if (size <= 0 || k <= 0) {
        return;
    }

    if (k == 1) {
        std::transform(first, last, dFirst, policy);
        return;
    }

    auto chunkSize = size / k;
    auto remainder = size % k;

    std::vector<std::jthread> threads;
    threads.reserve(k);

    auto currentInput = first;
    auto currentOutput = dFirst;

    for (int i = 0; i < k; ++i) {
        auto currentChunk = chunkSize + (i == k - 1 ? remainder : 0);
        auto nextInput = currentInput;
        std::advance(nextInput, currentChunk);

        threads.emplace_back([currentInput, nextInput, currentOutput, policy]() {
            std::transform(currentInput, nextInput, currentOutput, policy);
        });

        currentInput = nextInput;
        std::advance(currentOutput, currentChunk);
    }
}
