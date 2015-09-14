/*
 * Filename: SimulatedAnnealing.h
 * Author:   Michael Tkach (x1mike7x@gmail.com)
 */


#ifndef SIMULATEDANNEALING_H_7995D012_57FC_11E5_A91D_C038963D1C06
#define SIMULATEDANNEALING_H_7995D012_57FC_11E5_A91D_C038963D1C06


#include <vector>


namespace CleverAlgorithms
{

class SimulatedAnnealing
{
public:

    struct Candidate
    {
        std::vector<int> permutation;
        float cost;
    };


    static Candidate search(const std::vector<std::pair<float, float>>& cities,
                            const int kIterLimit,
                            const float kMaxTemperature,
                            const float kTemperatureChange);
};

} /* namespace CleverAlgorithms */

#endif /* SIMULATEDANNEALING_H_7995D012_57FC_11E5_A91D_C038963D1C06 */
