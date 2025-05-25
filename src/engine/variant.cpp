#include "variant.h"

#include <iostream>

Variant::Variant(const VariantType type, void *value) 
    : _type(type), _value(value) {}

VariantType Variant::get_type() {
    return _type;
}

float Variant::as_float() {
    if (_type != VariantType::FLOAT) {
        throw "Variant is not a float.";
    }
    return *static_cast<float*>(_value);
}

Vector2 Variant::as_vector2() {
    if (_type != VariantType::VECTOR2) {
        throw "Variant is not a Vector2.";
    }
    return *static_cast<Vector2*>(_value);
}

Vector3 Variant::as_vector3() {
    if (_type != VariantType::VECTOR3) {
        throw "Variant is not a Vector3.";
    }
    return *static_cast<Vector3*>(_value);
}

Color Variant::as_color() {
    if (_type != VariantType::COLOR) {
        throw "Variant is not a color.";
    }
    return *static_cast<Color*>(_value);
}

const std::string Variant::to_serializable_string() {
    switch (get_type()) {
        case VariantType::FLOAT: {
            return std::to_string(as_float());
        }
        case VariantType::VECTOR2: {
            auto vector = as_vector2();
            return "Vector2(" + std::to_string(vector.x) + "," + 
                    std::to_string(vector.y) + ")";
        }
        case VariantType::VECTOR3: {
            auto vector = as_vector3();
            return "Vector3(" + std::to_string(vector.x) + "," +
                   std::to_string(vector.y) + "," +
                   std::to_string(vector.z) + ")";
        }
        case VariantType::COLOR: {
            auto color = as_color();
            return "Color(" + std::to_string(color.r) + "," +
                   std::to_string(color.g) + "," +
                   std::to_string(color.b) + "," +
                   std::to_string(color.a) + ")";
        }
    }
    return "unknown";
}
