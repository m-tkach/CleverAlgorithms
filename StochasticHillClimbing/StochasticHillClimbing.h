/*
 * Filename: StochasticHillClimbing.h
 * Author:   Michael Tkach (x1mike7x@gmail.com)
 */


#ifndef STOCHASTICHILLCLIMBING_H_53DDEA50_28BD_11E5_9058_C038963D1C06
#define STOCHASTICHILLCLIMBING_H_53DDEA50_28BD_11E5_9058_C038963D1C06


#include <vector>


namespace CleverAlgorithms
{

class StochasticHillClimbing
{
public:

    struct Candidate
    {
        std::vector<bool> values;
        int cost;
    };


    static Candidate search(const int kIterLimit, const int kBitsCount);
};

} /* namespace CleverAlgorithms */

#endif /* STOCHASTICHILLCLIMBING_H_53DDEA50_28BD_11E5_9058_C038963D1C06 */
