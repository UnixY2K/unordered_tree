#include <optional>
#include <string>
#include <vector>

#include <unordered_tree/node.hpp>
#include <unordered_tree/node_value.hpp>

namespace ouroboros {

Node::Node(std::string const &id) : id{id} {}
Node::Node(std::string &&id) noexcept : id{std::move(id)} {}
Node::Node(NodeValue const &value) : value{value} {}
Node::Node(NodeValue &&value) noexcept : value{std::move(value)} {}
Node::Node(std::vector<NodeValue> const &value) : value{value} {}
Node::Node(std::vector<NodeValue> &&value) noexcept : value{std::move(value)} {}
Node::Node(std::string const &id, NodeValue const &value)
    : id{id}, value{value} {}
Node::Node(std::string &&id, NodeValue &&value) noexcept
    : id{std::move(id)}, value{std::move(value)} {}
Node::Node(std::string const &id, std::vector<NodeValue> const &value)
    : id{id}, value{value} {}
Node::Node(std::string &&id, std::vector<NodeValue> &&value) noexcept
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

std::optional<std::reference_wrapper<const std::vector<NodeValue>>>
Node::as_vector() const {
	if (std::holds_alternative<std::vector<NodeValue>>(value)) {
		std::vector<NodeValue> const &val =
		    std::get<std::vector<NodeValue>>(value);
		return std::ref(val);
	}
	return std::nullopt;
}

std::optional<std::reference_wrapper<std::vector<NodeValue>>>
Node::as_vector() {
	if (std::holds_alternative<std::vector<NodeValue>>(value)) {
		std::vector<NodeValue> &val = std::get<std::vector<NodeValue>>(value);
		return std::ref(val);
	}
	return std::nullopt;
}

void Node::set_value(Node const &node) { value = NodeValue{node}; }
void Node::set_value(Node &&node) noexcept {
	value = NodeValue{std::move(node)};
}
void Node::set_value(std::vector<NodeValue> const &vector) { value = vector; }
void Node::set_value(std::vector<NodeValue> &&vector) noexcept {
	value = std::move(vector);
}

Node &Node::operator=(NodeValue const &other) {
	value = other;
	return *this;
}
Node &Node::operator=(NodeValue &&other) noexcept {
	value = std::move(other);
	return *this;
}
Node &Node::operator=(std::vector<NodeValue> const &other) {
	value = other;
	return *this;
}
Node &Node::operator=(std::vector<NodeValue> &&other) noexcept {
	value = std::move(other);
	return *this;
}

} // namespace ouroboros
