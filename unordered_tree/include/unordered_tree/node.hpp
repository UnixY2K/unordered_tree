#pragma once
#include <optional>
#include <string>
#include <variant>
#include <vector>

#include <unordered_tree/node_value.hpp>

namespace ouroboros {

class Node {
	using node_val_t = std::variant<NodeValue, std::vector<NodeValue>>;
	std::string id;
	// a node can contain 0(monostate/void) or more elements, if the list of
	// elements is 0 it is empty
	node_val_t value{std::monostate{}};

  public:
	Node() = default;
	Node(Node const &other) noexcept = default;
	Node(Node &&other) = default;
	Node(std::string const &id);
	Node(std::string &&id) noexcept;
	Node(NodeValue const &value);
	Node(NodeValue &&value) noexcept;
	Node(std::vector<NodeValue> const &value);
	Node(std::vector<NodeValue> &&value) noexcept;
	Node(std::string const &id, NodeValue const &value);
	Node(std::string &&id, NodeValue &&value) noexcept;
	Node(std::string const &id, std::vector<NodeValue> const &value);
	Node(std::string &&id, std::vector<NodeValue> &&value) noexcept;

	void set_id(std::string const &new_id);
	void set_id(std::string &&new_id) noexcept;
	std::string_view get_id() const;

	bool is_empty() const;
	bool is_scalar() const;
	bool is_node() const;
	bool is_vector() const;

	std::optional<ScalarValue> as_scalar() const;
	std::optional<std::reference_wrapper<Node>> as_node() const;
	std::optional<std::reference_wrapper<const std::vector<NodeValue>>>
	as_vector() const;
	std::optional<std::reference_wrapper<std::vector<NodeValue>>> as_vector();

	template <typename T>
	    requires(DecaysToScalarType<T>)
	void set_value(T scalar) {
		value = ScalarValue{scalar};
	}

	void set_value(Node const &node);
	void set_value(Node &&node) noexcept;
	void set_value(std::vector<NodeValue> const &vector);
	void set_value(std::vector<NodeValue> &&vector) noexcept;

	template <typename T> constexpr bool is() const {
		if constexpr (std::is_same_v<T, ScalarValue>) {
			return is_scalar();
		} else if constexpr (std::is_same_v<T, Node>) {
			return is_node();
		} else if constexpr (std::is_same_v<T, std::vector<NodeValue>>) {
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
		} else if constexpr (std::is_same_v<T, std::vector<NodeValue>>) {
			return as_vector();
		} else {
			auto value = as_scalar();
			return value && value->as<T>();
		}
	}

	Node &operator=(Node const &other) noexcept = default;
	Node &operator=(Node &&other) = default;
	Node &operator=(NodeValue const &other);
	Node &operator=(NodeValue &&other) noexcept;
	Node &operator=(std::vector<NodeValue> const &other);
	Node &operator=(std::vector<NodeValue> &&other) noexcept;
};

} // namespace ouroboros
