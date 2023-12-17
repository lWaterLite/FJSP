#ifndef FJSP_UTILS_H
#define FJSP_UTILS_H

#include "json/json.hpp"
#include "Item.h"
#include <string>
#include <fstream>

using std::string;

string read_json_file(const string& file_path);
map<int, Item> parse_json(const string& json_string);


#endif //FJSP_UTILS_H
