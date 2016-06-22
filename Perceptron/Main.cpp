/*
 * Filename: Main.cpp
 * Author:   Michael Tkach (x1mike7x@gmail.com)
 */


#include "Perceptron.h"


int main()
{
    std::vector<std::pair<std::vector<size_t>, size_t>> orProblem = {
                                                                        {{0, 0}, 0},
                                                                        {{0, 1}, 1},
                                                                        {{1, 0}, 1},
                                                                        {{1, 1}, 1}
                                                                    };
    const size_t kInputs = 2;
    const size_t kIterations = 20;
    const float kLearningRate = 0.1f;

    (void)CleverAlgorithms::Perceptron::execute(orProblem, kInputs, kIterations, kLearningRate);
    return 0;
}

