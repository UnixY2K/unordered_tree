#include <functional>
#include <memory>
#include <optional>
#include <unordered_tree/node.hpp>

ScalarValue::ScalarValue(const ScalarValue &other) : value(other.value) {}
ScalarValue::ScalarValue(ScalarValue &&other) noexcept
    : value(std::move(other.value)) {}
ScalarValue::ScalarValue(scalar_t value) : value(value) {}

NodeVariant::NodeVariant() : value{new Node{}} {}
NodeVariant::NodeVariant(NodeVariant const &other)
    : value{new Node{other.get_value()}} {}
NodeVariant::NodeVariant(NodeVariant &&other) : value{std::move(other.value)} {
	// reset the value of the other variant so it does not have a invalid
	// pointer
	other.value.reset(new Node{});
}
NodeVariant::NodeVariant(Node const &node) : value{new Node{node}} {}
NodeVariant::NodeVariant(Node &&node) : value{new Node{std::move(node)}} {}
std::reference_wrapper<Node> NodeVariant::get_value() const {
	return std::ref(*value);
}
NodeVariant &NodeVariant::operator=(NodeVariant const &other) {
	value.reset(new Node{other.get_value()});
	return *this;
}
NodeVariant &NodeVariant::operator=(NodeVariant &&other) {
	value = std::move(other.value);
	other.value.reset(new Node{});
	return *this;
}

NodeValue::NodeValue(NodeValue const &other) : value(std::move(other.value)) {}
NodeValue::NodeValue(NodeValue &&other) noexcept
    : value(std::move(other.value)) {}
NodeValue::NodeValue(Node &&value) : value(NodeVariant(std::move(value))) {}

NodeValue::NodeValue(ScalarValue scalar) : value(std::move(scalar)) {}
bool NodeValue::is_scalar() const {
	return std::holds_alternative<ScalarValue>(value);
}
bool NodeValue::is_node() const {
	return std::holds_alternative<NodeVariant>(value);
}
std::optional<ScalarValue> NodeValue::as_scalar() const {
	return is_scalar() ? std::make_optional(std::get<ScalarValue>(value))
	                   : std::nullopt;
}

std::optional<std::reference_wrapper<Node>> NodeValue::as_node() const {
	return std::nullopt;
	return is_node()
	           ? std::make_optional(std::get<NodeVariant>(value).get_value())
	           : std::nullopt;
}
