#include <functional>
#include <optional>
#include <unordered_tree/node.hpp>

ScalarValue::ScalarValue(const ScalarValue &other) : value(other.value) {}
ScalarValue::ScalarValue(ScalarValue &&other) noexcept
    : value(std::move(other.value)) {}
ScalarValue::ScalarValue(scalar_t value) : value(value) {}

NodeValue::NodeValue(Node &&value)
    : value(std::unique_ptr<Node>(new Node(std::move(value)))) {}
NodeValue::NodeValue(std::unique_ptr<Node> &&value) : value(std::move(value)) {}
NodeValue::NodeValue(NodeValue &&other) noexcept
    : value(std::move(other.value)) {}
NodeValue::NodeValue(ScalarValue scalar) : value(std::move(scalar)) {}
bool NodeValue::is_scalar() const {
	return std::holds_alternative<ScalarValue>(value);
}
bool NodeValue::is_node() const {
	return std::holds_alternative<std::unique_ptr<Node>>(value);
}
std::optional<ScalarValue> NodeValue::as_scalar() const {
	return is_scalar() ? std::make_optional(std::get<ScalarValue>(value))
	                   : std::nullopt;
}

std::optional<std::reference_wrapper<Node>> NodeValue::as_node() const {
	return is_node() ? std::make_optional(
	                       std::ref(*std::get<std::unique_ptr<Node>>(value)))
	                 : std::nullopt;
}
