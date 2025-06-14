#include <algorithm>

#include <unordered_tree/node.hpp>
#include <unordered_tree/node_value.hpp>

namespace ouroboros {

NodeVariant::NodeVariant() : value{new Node{}} {}
NodeVariant::NodeVariant(NodeVariant const &other)
    : value{new Node{other.get_value()}} {}
NodeVariant::NodeVariant(NodeVariant &&other) : value{std::move(other.value)} {
	// reset the value of the other variant so it does not have a invalid
	// pointer
	other.value.reset(new Node{});
}
NodeVariant::NodeVariant(Node const &node) : value{new Node{node}} {}
NodeVariant::NodeVariant(Node &&node) : value{std::make_unique<Node>(node)} {}
std::reference_wrapper<Node> NodeVariant::get_value() const {
	return std::ref(*value);
}
NodeVariant &NodeVariant::operator=(Node const &other) {
	value.reset(new Node{other});
	return *this;
}
NodeVariant &NodeVariant::operator=(Node &&other) noexcept {
	*value = std::move(other);
	return *this;
}
NodeVariant &NodeVariant::operator=(NodeVariant const &other) {
	value.reset(new Node{other.get_value()});
	return *this;
}
NodeVariant &NodeVariant::operator=(NodeVariant &&other) noexcept {
	value = std::move(other.value);
	other.value.reset(new Node{});
	return *this;
}

} // namespace ouroboros
