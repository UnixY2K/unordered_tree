#include <algorithm>
#include <format>
#include <iostream>
#include <memory>
#include <optional>
#include <string>
#include <unordered_set>
#include <variant>
#include <vector>

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
	ScalarValue(const ScalarValue &other) : value(other.value) {}
	ScalarValue(ScalarValue &&other) noexcept : value(std::move(other.value)) {}
	explicit ScalarValue(scalar_t value) : value(value) {}

	template <typename T>
	    requires DecaysToScalarType<T> bool
	is() const {
		return std::holds_alternative<std::decay_t<T>>(value);
	}

	template <typename T>
	    requires(!DecaysToScalarType<T>) bool
	is() const {
		return false;
	}
	// value if is of the given type if not nothing
	template <typename T> std::optional<T> as() const {
		return is<T>() ? std::get<T>(value) : std::nullopt;
	}
};

class Node;

/*
 * helper class that can contain a scalar value or a node within
 */
class NodeValue {
	using node_t = std::variant<ScalarValue, std::unique_ptr<Node>>;
	node_t value = ScalarValue{};

  public:
	NodeValue() = default;
	explicit NodeValue(node_t value) : value(std::move(value)) {}
	NodeValue(NodeValue &&other) noexcept : value(std::move(other.value)) {}
	NodeValue(ScalarValue scalar) : value(std::move(scalar)) {}

	bool is_scalar() const {
		return std::holds_alternative<ScalarValue>(value);
	}

	bool is_node() const {
		return std::holds_alternative<std::unique_ptr<Node>>(value);
	}

	std::optional<ScalarValue> as_scalar() const {
		return is_scalar() ? std::make_optional(std::get<ScalarValue>(value))
		                   : std::nullopt;
	}

	std::optional<std::reference_wrapper<Node>> as_node() const {
		return is_node() ? std::make_optional(std::ref(
		                       *std::get<std::unique_ptr<Node>>(value)))
		                 : std::nullopt;
	}

	template <typename T> constexpr bool is() const {
		if constexpr (std::is_same_v<T, ScalarValue>) {
			return is_scalar();
		} else if constexpr (std::is_same_v<T, Node>) {
			return is_node();
		} else {
			auto value = as_scalar();
			return value && value->is<T>();
		}
	}
};

class Node {};

int main() {
	NodeValue value{ScalarValue{42}};
	bool is_scalar = value.is<ScalarValue>(); // returns true
	bool is_node = value.is<Node>();          // returns false
	bool is_int = value.is<int>();            // returns true
	std::cout << std::format("is_scalar: {}\n", is_scalar);
	std::cout << std::format("is_node: {}\n", is_node);
	std::cout << std::format("is_int: {}\n", is_int);
}
