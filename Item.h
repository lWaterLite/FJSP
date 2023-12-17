#ifndef FJSP_ITEM_H
#define FJSP_ITEM_H

#include <map>
#include "Job.h"

using std::map;

class Item {
    int index = -1;
public:
    map<int, Job> jobs;

    Item() = default;
    explicit Item(int index);
};


#endif //FJSP_ITEM_H
