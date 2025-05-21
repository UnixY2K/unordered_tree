#include <optional>
#include <string>
#include <string_view>
#include <vector>

#include <unordered_tree/node.hpp>
#include <unordered_tree/node_value.hpp>
#include <unordered_tree/scalar_value.hpp>

namespace ouroboros {

Node::Node(std::string const &id) : id{id} {}
Node::Node(std::string &&id) noexcept : id{std::move(id)} {}
Node::Node(NodeValue const &value) : value{value} {}
Node::Node(NodeValue &&value) noexcept : value{std::move(value)} {}
Node::Node(NodeVector const &value) : value{value} {}
Node::Node(NodeVector &&value) noexcept : value{std::move(value)} {}
Node::Node(std::initializer_list<NodeValue> init_list)
    : value(NodeVector(init_list)) {}
Node::Node(std::string const &id, NodeValue const &value)
    : id{id}, value{value} {}
Node::Node(std::string &&id, NodeValue &&value) noexcept
    : id{std::move(id)}, value{std::move(value)} {}
Node::Node(std::string const &id, NodeVector const &value)
    : id{id}, value{value} {}
Node::Node(std::string &&id, NodeVector &&value) noexcept
    : id{std::move(id)}, value{std::move(value)} {}

void Node::set_id(std::string const &new_id) { id = new_id; }
void Node::set_id(std::string &&new_id) noexcept { id = std::move(new_id); }
std::string_view Node::get_id() const { return id; }

bool Node::is_empty() const {
	auto scalar = as_scalar();
	if (scalar) {
		return scalar->is<void>();
	}
	return false;
}

bool Node::is_scalar() const {
	auto scalar = as_scalar();
	if (scalar) {
		return !scalar->is<void>();
	}
	return false;
}

bool Node::is_node() const {
	auto node = as_node();
	if (node) {
		return true;
	}
	return false;
}

bool Node::is_vector() const {
	auto vector = as_vector();
	if (vector) {
		return true;
	}
	return false;
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
