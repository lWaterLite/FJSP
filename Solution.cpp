//
// Created by low_c on 12/14/2023.
//

#include "Solution.h"
#include <algorithm>
#include <random>
#include <cmath>

using std::fill;
using std::random_device;
using std::mt19937;
using std::uniform_int_distribution;
using std::uniform_real_distribution;
using std::shuffle;
using std::advance;
using std::max;
using std::max_element;
using std::swap;

Solution::Solution(const map<int, Item>& items, double begin_temperature, double end_temperature, double temperature_factor) {
    random_device rd;
    int t = -1;
    this->item_number = (int)items.size();
    this->rng = mt19937(rd());
    this->begin_temperature = begin_temperature;
    this->end_temperature = end_temperature;
    this->temperature_factor = temperature_factor;

    for (const auto& item: items) {
        int job_number = (int)item.second.jobs.size();
        for (int i = 0; i < job_number; ++i) {
            this->item_sequence.push_back(item.first);
        }
        for (const auto& job: item.second.jobs) {
            for (const auto& machine_time: job.second.job_machine) {
                if (machine_time.first > t) t = machine_time.first;
            }
        }
    }
    this->machine_number = t;
    shuffle(this->item_sequence.begin(), this->item_sequence.end(), this->rng);
}

void Solution::GenerateSequence(map<int, Item> &items) {
    this->machine_sequence.clear();
    this->time_sequence.clear();

    // 邻域搜索
    uniform_int_distribution<int> uni1(0, (int)this->item_sequence.size() - 2);
    int r = uni1(this->rng);
    swap(this->item_sequence[r], this->item_sequence[r+1]);

    vector<int> current_job;
    for (int i = 0; i < items.size(); ++i) {
        current_job.push_back(0);
    }
    current_job.push_back(0);    // start from 1

    for (const auto item_index: this->item_sequence) {
        int current = ++current_job[item_index];
        map<int, int>& time_map = items[item_index].jobs[current].job_machine;

        uniform_int_distribution<int> uni(0, (int)time_map.size() - 1);
        int random_index = uni(this->rng);
        auto it = time_map.begin();
        advance(it, random_index);

        this->machine_sequence.push_back(it->first);
        this->time_sequence.push_back(it->second);
    }
}

void Solution::CalculateTime() {
    int t_time = 0;
    vector<int> item_status;
    vector<int> machine_status;
    for (int i = 0; i < this->item_number; ++i) {
        item_status.push_back(0);
    }
    item_status.push_back(0); // start from 1;
    for (int i = 0; i < this->machine_number; ++i) {
        machine_status.push_back(0);
    }
    machine_status.push_back(0); // start from 1;

    int pos = 0;
    while (pos < this->item_sequence.size()) {
        auto& i_current = item_status[this->item_sequence[pos]];
        auto& m_current = machine_status[this->machine_sequence[pos]];
        if (i_current ==0 && m_current == 0) {
            i_current = this->time_sequence[pos];
            m_current = this->time_sequence[pos];
            pos++;
            continue;
        }

        int bg_time = max(i_current, m_current);
        t_time += bg_time;
        for (auto& t: item_status) {
            if (t > 0) t = (t - bg_time > 0) ? (t - bg_time) : 0;
        }
        for (auto& t: machine_status) {
            if (t > 0) t = (t - bg_time > 0) ? (t - bg_time) : 0;
        }
        pos++;
    }
    int maxElement = *max_element(item_status.begin(), item_status.end());
    t_time += maxElement;
    this->epoch_time = t_time;
}

void Solution::SimulateAnnealing() {
    if (this->epoch_time < this->final_time) this->final_time = this->epoch_time;
    else {
        auto possibility = exp((this->final_time - this->epoch_time) / this->begin_temperature);
        uniform_real_distribution uni(0.0, 1.0);
        auto r = uni(this->rng);
        if (possibility > r) this->final_time = this->epoch_time;
    }
}

bool Solution::IsCooled() const {
    return (this->begin_temperature < this->end_temperature);
}

void Solution::Cooling() {
    this->begin_temperature = this->begin_temperature * this->temperature_factor;
}

int Solution::getFinalTime() const {
    return this->final_time;
}

vector<int> Solution::getItemSequence() const{
    return this->item_sequence;
}

vector<int> Solution::getMachineSequence() const {
    return this->machine_sequence;
}

vector<int> Solution::getTimeSequence() const {
    return this->time_sequence;
}


