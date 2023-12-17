#include "utils.h"
#include "Item.h"
#include <map>

using nlohmann::json;
using std::ifstream;
using std::map;

string read_json_file(const string& file_path) {
    ifstream file(file_path);
    if (!file.is_open()) {
        throw std::runtime_error("Can't open json file.");
    }

    string json_string, line;
    while (getline(file, line)) {
        json_string += line;
    }

    return json_string;
}

map<int, Item> parse_json(const string& json_string) {
    map<int, Item> items;

    json job_json = json::parse(json_string);
    for (const auto& j_job: job_json["job_list"]) {
        int item_id = j_job["item_id"];
        int job_id = j_job["job_id"];
        map<int, int> machine_time;
        for (const auto& m_time: j_job["machine_map"]) {
            int machine_id = m_time["machine_id"];
            machine_time[machine_id] = m_time["work_time"];
        }
        Job job = Job(item_id, job_id);
        job.job_machine = machine_time;

        auto it=items.find(item_id);
        if (it == items.end()) {
            auto item = Item(item_id);
            item.jobs[job_id] = job;
            items[item_id] = item;
        }
        else {
            it->second.jobs[job_id] = job;
        }
    }

    return items;
}

