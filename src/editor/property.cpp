#include "property.h"

Property::Property(const std::string &name, const std::string &group_name, const std::function<Variant()> get_function, const std::function<void(Variant)>  set_function) 
    : name(name), group_name(group_name), get_function(get_function), set_function(set_function) {}
