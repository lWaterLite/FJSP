#ifndef FJSP_SOLUTION_H
#define FJSP_SOLUTION_H

#include "Item.h"
#include <vector>
#include <map>
#include <algorithm>
#include <random>

using std::vector;
using std::map;
using std::random_device;
using std::mt19937;

class Solution {
    mt19937 rng;
    vector<int> item_sequence;
    vector<int> machine_sequence;
    vector<int> time_sequence;
    double begin_temperature;
    double end_temperature;
    double temperature_factor;
    int final_time = -1;
    int epoch_time = -1;
    int item_number;
    int machine_number;

public:
    Solution(const map<int, Item>& items, double begin_temperature, double end_temperature, double temperature_factor);
    void GenerateSequence(map<int, Item>& items);
    void CalculateTime();
    void SimulateAnnealing();
    void Cooling();
    [[nodiscard]] bool IsCooled() const;
    [[nodiscard]] int getFinalTime() const;
    [[nodiscard]] vector<int> getItemSequence() const;
    [[nodiscard]] vector<int> getMachineSequence() const;
    [[nodiscard]] vector<int> getTimeSequence() const;
};


#endif //FJSP_SOLUTION_H
