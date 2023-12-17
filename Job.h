#ifndef FJSP_JOB_H
#define FJSP_JOB_H

#include <map>

using std::map;

class Job {
    int item_id = -1;
    int job_id = -1;
public:
    map<int, int> job_machine; // key for machine index, value for time.

    Job() = default;
    Job(int item_id, int job_id);
};


#endif //FJSP_JOB_H
