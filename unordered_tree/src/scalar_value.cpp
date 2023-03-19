#include <unordered_tree/scalar_value.hpp>

ScalarValue::ScalarValue(const ScalarValue &other) : value(other.value) {}
ScalarValue::ScalarValue(ScalarValue &&other) noexcept
    : value(std::move(other.value)) {}
ScalarValue::ScalarValue(scalar_t value) : value(value) {}
