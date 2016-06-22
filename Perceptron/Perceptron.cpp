/*
 * Filename: Perceptron.cpp
 * Author:   Michael Tkach (x1mike7x@gmail.com)
 */


#include <algorithm>
#include <cassert>
#include <ctime>
#include <iostream>

#include "Perceptron.h"


namespace CleverAlgorithms
{

namespace
{

inline float random(const float left, const float right)
{
    assert(left <= right);
    return left + (right - left) * (static_cast<float>(rand()) / RAND_MAX);
}


inline std::vector<float> randomVector(const std::vector<std::pair<float, float>>& bounds)
{
    std::vector<float> res(bounds.size());
    for (size_t i = 0; i < bounds.size(); ++i)
    {
        res[i] = random(bounds[i].first, bounds[i].second);
    }
    return res;
}


inline std::vector<float> initializeWeights(const size_t problemSize)
{
    std::vector<std::pair<float, float>> bounds(problemSize + 1, {-1.0f, 1.0f});
    return randomVector(bounds);
}


void updateWeights(const size_t numInputs,
                   std::vector<float>& weights,
                   const std::vector<size_t>& input,
                   const float outExpected,
                   const float outActual,
                   const float learningRate)
{
    assert(numInputs == input.size());
    assert(weights.size() == input.size() + 1);

    for (size_t i = 0; i < numInputs; ++i)
    {
        weights[i] += learningRate * (outExpected - outActual) * input[i];
    }
    weights.back() += learningRate * (outExpected - outActual) * 1.0f;
}


float activate(const std::vector<float>& weights, const std::vector<size_t>& vector)
{
    assert(weights.size() == vector.size() + 1);

    float sum = weights.back() * 1.0f;
    for (size_t i = 0; i < vector.size(); ++i)
    {
        sum += weights[i] * vector[i];
    }
    return sum;
}


float transfer(float activation)
{
    return (activation >= 0.0f) ? 1.0f : 0.0f;
}


float getOutput(const std::vector<float>& weights, const std::vector<size_t>& vector)
{
    float activation = activate(weights, vector);
    return transfer(activation);
}


void trainWeights(std::vector<float>& weights,
                  const std::vector<std::pair<std::vector<size_t>, size_t>>& domain,
                  const size_t numInputs,
                  const size_t iterations,
                  const float learningRate)
{
    for (size_t epoch = 0; epoch < iterations; ++epoch)
    {
        float error = 0.0f;
        for (const auto& pattern: domain)
        {
            const std::vector<size_t>& input = pattern.first;
            float expected = static_cast<float>(pattern.second);
            float output = getOutput(weights, input);
            error += std::abs(output - expected);
            updateWeights(numInputs, weights, input, expected, output, learningRate);
        }
        std::clog << "Train epoch #" << epoch << ": error = " << error << "\n";
    }
}


size_t testWeights(const std::vector<float>& weights,
                   const std::vector<std::pair<std::vector<size_t>, size_t>>& domain,
                   const size_t numInputs)
{
    size_t correct = 0;
    for (const auto& pattern: domain)
    {
        const std::vector<size_t>& input = pattern.first;
        float output = getOutput(weights, input);
        correct += (static_cast<size_t>(output + std::numeric_limits<float>::epsilon()) == pattern.second) ? 1 : 0;
    }
    std::clog << "Test result: " << 100.f * correct / domain.size() << "%\n";
    return correct;
}

} /* anonymous namespace */


std::vector<float> Perceptron::execute(const std::vector<std::pair<std::vector<size_t>, size_t>>& domain,
                                       const size_t inputs,
                                       const size_t iterations,
                                       const float learningRate)
{
    srand(static_cast<unsigned>(time(nullptr)));

    std::vector<float> weights = initializeWeights(inputs);
    trainWeights(weights, domain, inputs, iterations, learningRate);
    (void)testWeights(weights, domain, inputs);
    return weights;
}

} /* namespace CleverAlgorithms */
