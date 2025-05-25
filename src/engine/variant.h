#pragma once

#include "math/vector2.h"
#include "math/vector3.h"
#include "math/color.h"
#include <any>

enum VariantType {
    NIL, // Had to call it nil because null and NULL are already reserved
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

    const std::string to_string();
    const static Variant from_string(const std::string &string);

    const static Variant nil;
private:
    void *_value;
    VariantType _type;
};
