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