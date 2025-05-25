#pragma once

#include "math/vector2.h"
#include "math/vector3.h"
#include "math/color.h"
#include <any>

enum VariantType {
    FLOAT,
    VECTOR2,
    VECTOR3,
    COLOR
};

struct Variant {
public:
    Variant(const VariantType type, void *value);
    
    VariantType get_type();
    float as_float();
    Vector2 as_vector2();
    Vector3 as_vector3();
    Color as_color();

    const std::string to_serializable_string();
private:
    void *_value;
    VariantType _type;
};
