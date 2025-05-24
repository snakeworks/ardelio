#pragma once

#include "math/vector3.h"
#include "math/color.h"
#include <any>

enum VariantType {
    FLOAT,
    VECTOR3,
    COLOR
};

struct Variant {
public:
    Variant(const VariantType type, void *value);
    
    VariantType get_type();
    float as_float();
    Vector3 as_vector3();
    Color as_color();
private:
    void *_value;
    VariantType _type;
};
