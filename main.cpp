#include <iostream>
#include <map>
#include <chrono>
#include "utils.h"
#include "Item.h"
#include "Solution.h"

#define EPOCHS 400
#define BEGIN_TEMP 1000
#define END_TEMP 0.001
#define TEMP_FACTOR 0.98

using std::map;
using std::cout;
using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::seconds;

int main() {
    map<int, Item> items;
    items = parse_json(read_json_file("object.json"));
    Solution solution(items, BEGIN_TEMP, END_TEMP, TEMP_FACTOR);
    int epochs = 0;

    auto start_time =  high_resolution_clock::now();

    while (!solution.IsCooled()) {
        epochs++;
        solution.GenerateSequence(items);
        solution.CalculateTime();
        solution.SimulateAnnealing();

        if (epochs % EPOCHS == 0) solution.Cooling();
    }

    auto end_time = high_resolution_clock ::now();
    auto running_time = duration_cast<seconds>(end_time - start_time);

    cout << "Solution Completed.\n";
    cout << "Solution Running Time: " << running_time.count() << " seconds\n";
    cout << "Final Processing Time: " << solution.getFinalTime() << "\n";
    cout << "Item Sequence: ";
    for (const auto& i: solution.getItemSequence()) {
        cout << i << " ";
    }
    cout << "\n";
    cout << "Machine Sequence: ";
    for (const auto& i: solution.getMachineSequence()) {
        cout << i << " ";
    }
    cout << "\n";
    cout << "Time Sequence: ";
    for (const auto& i: solution.getTimeSequence()) {
        cout << i << " ";
    }
    cout << "\n";
    return 0;
}
