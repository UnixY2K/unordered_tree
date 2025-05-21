#include <string_view>
#include <unordered_tree/scalar_value.hpp>
#include <variant>

namespace ouroboros {

ScalarValue::ScalarValue(const ScalarValue &other) : value(other.value) {}
ScalarValue::ScalarValue(ScalarValue &&other) noexcept
    : value(std::move(other.value)) {}
ScalarValue::ScalarValue(scalar_t value) : value(value) {}

std::string_view ScalarValue::get_type() const {
	return visit<std::string_view>(overloads{
	    [](int const) -> std::string_view { return "int"; },
	    [](bool const) -> std::string_view { return "bool"; },
	    [](char const) -> std::string_view { return "char"; },
	    [](float const) -> std::string_view { return "float"; },
	    [](double const &) -> std::string_view { return "double"; },
	    [](std::string const &) -> std::string_view { return "string"; },
	    [](std::monostate const &) -> std::string_view { return "None"; },
	});
}

ScalarValue &ScalarValue::operator=(scalar_t const &value) {
	this->value = value;
	return *this;
}
} // namespace ouroboros
