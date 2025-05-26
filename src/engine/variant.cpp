#include "variant.h"

Variant::Variant(const VariantType type, void *value) 
    : _type(type), _value(value) {}

VariantType Variant::get_type() {
    return _type;
}

const Variant Variant::nil = Variant(VariantType::NIL, nullptr);

bool Variant::as_bool() {
    if (_type != VariantType::BOOL) {
        throw "Variant is not a bool.";
    }
    return *static_cast<bool*>(_value);
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
        throw "Variant is not a Color.";
    }
    return *static_cast<Color*>(_value);
}

const std::string Variant::to_string() {
    switch (get_type()) {
        case VariantType::NIL: {
            return "nil";
        }
        case VariantType::BOOL: {
            return as_bool() ? "true" : "false";
        }
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

Variant Variant::from_string(const std::string &string) {
    if (string.rfind("Vector2(", 0) == 0) {
        size_t start = string.find('(') + 1;
        size_t comma = string.find(',', start);
        size_t end = string.find(')', comma);
        float x = std::stof(string.substr(start, comma - start));
        float y = std::stof(string.substr(comma + 1, end - comma - 1));
        Vector2 *vector = new Vector2{x, y};
        return Variant(VariantType::VECTOR2, vector);
    } else if (string.rfind("Vector3(", 0) == 0) {
        size_t start = string.find('(') + 1;
        size_t first_comma = string.find(',', start);
        size_t second_comma = string.find(',', first_comma + 1);
        size_t end = string.find(')', second_comma);
        float x = std::stof(string.substr(start, first_comma - start));
        float y = std::stof(string.substr(first_comma + 1, second_comma - first_comma - 1));
        float z = std::stof(string.substr(second_comma + 1, end - second_comma - 1));
        Vector3 *vector = new Vector3{x, y, z};
        return Variant(VariantType::VECTOR3, vector);
    } else if (string.rfind("Color(", 0) == 0) {
        size_t start = string.find('(') + 1;
        size_t first_comma = string.find(',', start);
        size_t second_comma = string.find(',', first_comma + 1);
        size_t third_comma = string.find(',', second_comma + 1);
        size_t end = string.find(')', third_comma);
        uint8_t r = static_cast<uint8_t>(std::stoi(string.substr(start, first_comma - start)));
        uint8_t g = static_cast<uint8_t>(std::stoi(string.substr(first_comma + 1, second_comma - first_comma - 1)));
        uint8_t b = static_cast<uint8_t>(std::stoi(string.substr(second_comma + 1, third_comma - second_comma - 1)));
        uint8_t a = static_cast<uint8_t>(std::stoi(string.substr(third_comma + 1, end - third_comma - 1)));
        Color *color = new Color{r, g, b, a};
        return Variant(VariantType::COLOR, color);
    } else if (string == "true" || string == "false") {
        bool *bool_value = new bool(string == "true");
        return Variant(VariantType::BOOL, bool_value);
    } else {
        try {
            float value = std::stof(string);
            float *float_value = new float(value);
            return Variant(VariantType::FLOAT, float_value);
        } catch (...) {
            throw "Invalid string format for Variant.";
        }
    }
}
