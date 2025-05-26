#pragma once
#include <initializer_list>
#include <optional>
#include <variant>
#include <vector>

#include <unordered_tree/node_value.hpp>

namespace ouroboros {

using NodeVector = std::vector<NodeValue>;
class Node {
	using node_val_t = std::variant<NodeValue, NodeVector>;
	// a node can contain 0(monostate/void) or more elements, if the list of
	// elements is 0 it is empty
	node_val_t value{std::monostate{}};

  public:
	Node() = default;
	Node(Node const &other) noexcept = default;
	Node(Node &&other) = default;
	Node(NodeValue const &value);
	Node(NodeValue &&value) noexcept;
	Node(NodeVector const &value);
	Node(NodeVector &&value) noexcept;
	Node(std::initializer_list<NodeValue> init_list);

	bool is_empty() const;
	bool is_scalar() const;
	bool is_node() const;
	bool is_vector() const;

	std::optional<ScalarValue> as_scalar() const;
	std::optional<std::reference_wrapper<Node>> as_node() const;
	std::optional<std::reference_wrapper<const NodeVector>> as_vector() const;
	std::optional<std::reference_wrapper<NodeVector>> as_vector();

	template <typename T>
	    requires(DecaysToScalarType<T>)
	void set_value(T scalar) {
		value = ScalarValue{scalar};
	}

	void set_value(Node const &node);
	void set_value(Node &&node) noexcept;
	void set_value(NodeVector const &vector);
	void set_value(NodeVector &&vector) noexcept;

	template <typename T> constexpr bool is() const {
		if constexpr (std::is_same_v<T, ScalarValue>) {
			return is_scalar();
		} else if constexpr (std::is_same_v<T, Node>) {
			return is_node();
		} else if constexpr (std::is_same_v<T, NodeVector>) {
			return is_vector();
		} else {
			auto value = as_scalar();
			return value && value->is<T>();
		}
	}
	template <typename T> constexpr std::optional<T> as() const {
		if constexpr (std::is_same_v<T, ScalarValue>) {
			return as_scalar();
		} else if constexpr (std::is_same_v<T, Node>) {
			return as_node();
		} else if constexpr (std::is_same_v<T, NodeVector>) {
			return as_vector();
		} else {
			auto value = as_scalar();
			return value && value->as<T>();
		}
	}

	template <typename T, typename... Ts>
	T visit(const overloads<Ts...> &visitor) const {
		return std::visit(visitor, value);
	}
	std::string_view get_type() const;

	Node &operator=(Node const &other) noexcept = default;
	Node &operator=(Node &&other) = default;
	Node &operator=(NodeValue const &other);
	Node &operator=(NodeValue &&other) noexcept;
	Node &operator=(NodeVector const &other);
	Node &operator=(NodeVector &&other) noexcept;
};

} // namespace ouroboros
