#pragma once

#include <string>

class Resource {
public:
    Resource(const std::string &path = "");
    std::string get_path();
private:
    std::string _path;
};