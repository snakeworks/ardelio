#pragma once

#include "engine/variant.h"

#include <string>
#include <functional>

class Property {
public:
    Property(const std::string &name, const std::string &group_name, const std::function<Variant()> get_function, const std::function<void(Variant)> set_function);
    std::string name;
    std::string group_name;
    std::function<Variant()> get_function;
    std::function<void(Variant)> set_function;
};