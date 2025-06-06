#pragma once

#include "math/vector2.h"
#include "math/vector3.h"
#include "math/color.h"

enum VariantType {
    NIL, // Had to call it nil because null and NULL are already reserved
    BOOL,
    FLOAT,
    STRING,
    VECTOR2,
    VECTOR3,
    COLOR
};

struct Variant {
public:
    Variant(const VariantType type, void *value);
    
    VariantType get_type();
    
    bool as_bool();
    float as_float();
    std::string as_string();
    Vector2 as_vector2();
    Vector3 as_vector3();
    Color as_color();

    const std::string to_string();
    static Variant from_string(const std::string &string);

    const static Variant nil;
private:
    void *_value;
    VariantType _type;
};
