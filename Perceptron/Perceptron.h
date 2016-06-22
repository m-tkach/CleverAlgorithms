/*
 * Filename: Perceptron.h
 * Author:   Michael Tkach (x1mike7x@gmail.com)
 */


#ifndef PERCEPTRON_H_E63FD730_37EC_11E6_8CBB_C038963D1C06
#define PERCEPTRON_H_E63FD730_37EC_11E6_8CBB_C038963D1C06


#include <cstdlib>
#include <vector>


namespace CleverAlgorithms
{

class Perceptron
{
public:

    static std::vector<float> execute(const std::vector<std::pair<std::vector<size_t>, size_t>>& domain,
                                      const size_t inputs,
                                      const size_t iterations,
                                      const float learningRate);
};

} /* namespace CleverAlgorithms */

#endif /* PERCEPTRON_H_E63FD730_37EC_11E6_8CBB_C038963D1C06 */
