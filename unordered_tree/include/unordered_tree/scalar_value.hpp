#pragma once
#include <optional>
#include <string>
#include <type_traits>
#include <variant>

template <typename T>
concept DecaysToScalarType = std::is_same_v<std::decay_t<T>, int> ||
                             std::is_same_v<std::decay_t<T>, bool> ||
                             std::is_same_v<std::decay_t<T>, char> ||
                             std::is_same_v<std::decay_t<T>, float> ||
                             std::is_same_v<std::decay_t<T>, double> ||
                             std::is_same_v<std::decay_t<T>, std::string> ||
                             std::is_same_v<std::decay_t<T>, std::monostate>;

/*
 *  class that contains "scalar" values(None, int, float, double, bool, string)
 *  basically a leaf node
 */
class ScalarValue {
	using scalar_t = std::variant<int, bool, char, float, double, std::string,
	                              std::monostate>;
	scalar_t value = std::monostate{};

  public:
	ScalarValue() = default;
	ScalarValue(const ScalarValue &other);
	ScalarValue(ScalarValue &&other) noexcept;
	ScalarValue(scalar_t value);

	template <typename T>
	    requires(DecaysToScalarType<T>) bool
	is() const {
		return std::holds_alternative<std::decay_t<T>>(value);
	}

	template <typename T>
	    requires(!DecaysToScalarType<T>) bool
	is() const {
		// treat void as no value or std::monostate
		if constexpr (std::is_same_v<T, void>) {
			return std::holds_alternative<std::monostate>(value);
		} else {
			return false;
		}
	}
	// value if is of the given type if not nothing
	template <typename T> std::optional<T> as() const {
		return is<T>() ? std::get<T>(value) : std::optional<T>(std::nullopt);
	}

	ScalarValue &operator=(ScalarValue const &other) = default;
	ScalarValue &operator=(ScalarValue &&other) noexcept = default;
	ScalarValue &operator=(scalar_t const &value);
};
