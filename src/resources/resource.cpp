#include "resource.h"

Resource::Resource(const std::string &path)
    : _path(path) {}

std::string Resource::get_path() {
    return _path;
}