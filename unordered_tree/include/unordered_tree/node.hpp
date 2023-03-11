#pragma once
#include <algorithm>
#include <memory>
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
		return false;
	}
	// value if is of the given type if not nothing
	template <typename T> std::optional<T> as() const {
		return is<T>() ? std::get<T>(value) : std::nullopt;
	}
};

class Node;
class NodeValue;

/*
 * helper class that can contain a scalar value or a node within
 */
class NodeValue {
	using node_t = std::variant<ScalarValue, std::unique_ptr<Node>>;
	node_t value = ScalarValue{};

  public:
	NodeValue() = default;
	// explicit NodeValue(node_t value) : value(std::move(value)) {}
	NodeValue(Node &&value);
	NodeValue(std::unique_ptr<Node> &&value);
	NodeValue(NodeValue &&other) noexcept;
	NodeValue(ScalarValue scalar);
	template <typename T>
	    requires(DecaysToScalarType<T>)
	NodeValue(T scalar) : NodeValue(ScalarValue{scalar}){};

	bool is_scalar() const;
	bool is_node() const;

	std::optional<ScalarValue> as_scalar() const;

	std::optional<std::reference_wrapper<Node>> as_node() const;

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
