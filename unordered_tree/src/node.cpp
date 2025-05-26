#include <optional>

#include <string_view>

#include <unordered_tree/node.hpp>
#include <unordered_tree/node_value.hpp>
#include <unordered_tree/scalar_value.hpp>
#include <variant>

namespace ouroboros {

Node::Node(NodeValue const &value) : value{value} {}
Node::Node(NodeValue &&value) noexcept : value{std::move(value)} {}
Node::Node(NodeVector const &value) : value{value} {}
Node::Node(NodeVector &&value) noexcept : value{std::move(value)} {}
Node::Node(std::initializer_list<NodeValue> init_list)
    : value(NodeVector(init_list)) {}

bool Node::is_empty() const {
	auto scalar = as_scalar();
	return scalar && scalar->is<void>();
}

bool Node::is_scalar() const {
	auto scalar = as_scalar();
	return scalar && !scalar->is<void>();
}

bool Node::is_node() const { return std::holds_alternative<NodeValue>(value); }

bool Node::is_vector() const {
	return std::holds_alternative<NodeVector>(value);
}

std::optional<ScalarValue> Node::as_scalar() const {
	if (std::holds_alternative<NodeValue>(value)) {
		return std::get<NodeValue>(value).as_scalar();
	}
	return std::nullopt;
}

std::optional<std::reference_wrapper<Node>> Node::as_node() const {
	if (std::holds_alternative<NodeValue>(value)) {
		return std::get<NodeValue>(value).as_node();
	}
	return std::nullopt;
}

std::optional<std::reference_wrapper<const NodeVector>>
Node::as_vector() const {
	if (std::holds_alternative<NodeVector>(value)) {
		NodeVector const &val = std::get<NodeVector>(value);
		return std::ref(val);
	}
	return std::nullopt;
}

std::optional<std::reference_wrapper<NodeVector>> Node::as_vector() {
	if (std::holds_alternative<NodeVector>(value)) {
		NodeVector &val = std::get<NodeVector>(value);
		return std::ref(val);
	}
	return std::nullopt;
}

void Node::set_value(Node const &node) { value = NodeValue{node}; }
void Node::set_value(Node &&node) noexcept {
	value = NodeValue{std::move(node)};
}
void Node::set_value(NodeVector const &vector) { value = vector; }
void Node::set_value(NodeVector &&vector) noexcept {
	value = std::move(vector);
}

std::string_view Node::get_type() const {
	return visit<std::string_view>(overloads{
	    [](const NodeValue &node) -> std::string_view {
		    return node.get_type();
	    },
	    [](const NodeVector &) -> std::string_view { return "NodeVector"; },
	});
}

Node &Node::operator=(NodeValue const &other) {
	value = other;
	return *this;
}
Node &Node::operator=(NodeValue &&other) noexcept {
	value = std::move(other);
	return *this;
}
Node &Node::operator=(NodeVector const &other) {
	value = other;
	return *this;
}
Node &Node::operator=(NodeVector &&other) noexcept {
	value = std::move(other);
	return *this;
}

} // namespace ouroboros
