#include <unordered_tree/scalar_value.hpp>

namespace ouroboros {

ScalarValue::ScalarValue(const ScalarValue &other) : value(other.value) {}
ScalarValue::ScalarValue(ScalarValue &&other) noexcept
    : value(std::move(other.value)) {}
ScalarValue::ScalarValue(scalar_t value) : value(value) {}

ScalarValue &ScalarValue::operator=(scalar_t const &value) {
	this->value = value;
	return *this;
}
} // namespace ouroboros
