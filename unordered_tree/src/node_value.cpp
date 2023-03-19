#include <unordered_tree/node.hpp>
#include <unordered_tree/node_value.hpp>

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
