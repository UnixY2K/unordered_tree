
#include <initializer_list>
#include <unordered_tree/node.hpp>
#include <unordered_tree/node_value.hpp>

namespace ouroboros {

NodeValue::NodeValue(NodeValue const &other) : value((other.value)) {}
NodeValue::NodeValue(NodeValue &&other) noexcept
    : value(std::move(other.value)) {}
NodeValue::NodeValue(Node const &value) : value{value} {}
NodeValue::NodeValue(Node &&value) noexcept : value{Node(value)} {}
NodeValue::NodeValue(ScalarValue const &scalar) : value(scalar) {}
NodeValue::NodeValue(ScalarValue &&scalar) noexcept : value(scalar) {}
NodeValue::NodeValue(NodeVector const &vector) : value(NodeVariant(vector)) {}
NodeValue::NodeValue(NodeVector &&vector) noexcept
    : value(NodeVariant(std::move(vector))) {}
NodeValue::NodeValue(NodeDictionary const &dictionary)
    : value(NodeVariant(dictionary)) {}
NodeValue::NodeValue(NodeDictionary &&dictionary) noexcept
    : value(NodeVariant(std::move(dictionary))) {}
NodeValue::NodeValue(std::initializer_list<NodeValue> children)
    : value(Node(children)) {}
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
	return is_node()
	           ? std::make_optional(std::get<NodeVariant>(value).get_value())
	           : std::nullopt;
}

std::string_view NodeValue::get_type() const {
	return visit<std::string_view>(overloads{
	    [](const ScalarValue &scalar) -> std::string_view {
		    return scalar.get_type();
	    },
	    [](const NodeVariant &) -> std::string_view { return "Node"; },
	});
}

NodeValue &NodeValue::operator=(Node const &other) {
	value = other;
	return *this;
}
NodeValue &NodeValue::operator=(Node &&other) noexcept {
	value = std::move(other);
	return *this;
}

} // namespace ouroboros
