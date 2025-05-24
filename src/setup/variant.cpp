#include "variant.h"

Variant::Variant(const VariantType type, void *value) 
    : _type(type), _value(value) {}

VariantType Variant::get_type() {
    return _type;
}

float Variant::as_float() {
    if (_type != VariantType::FLOAT) {
        return -1.0f;
    }
    return *static_cast<float*>(_value);
}

Vector3 Variant::as_vector3() {
    if (_type != VariantType::VECTOR3) {
        return Vector3::zero;
    }
    return *static_cast<Vector3*>(_value);
}