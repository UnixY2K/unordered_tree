#include <format>
#include <iostream>

#include <unordered_tree/node.hpp>
#include <unordered_tree/node_value.hpp>
#include <unordered_tree/scalar_value.hpp>

int main() {
	using ouroboros::Node;
	using ouroboros::NodeValue;
	using ouroboros::NodeVariant;
	using ouroboros::ScalarValue;

	NodeValue value{1};
	value = Node{};
	value = NodeValue{};
	bool is_scalar = value.is<ScalarValue>(); // returns true
	bool is_node = value.is<Node>();          // returns false
	std::string_view type = value.get_type();
	std::cout << std::format("is_scalar: {}\n", is_scalar);
	std::cout << std::format("is_node  : {}\n", is_node);
	std::cout << std::format("type     : {}\n", type);

	Node root = {1, 2, {3, 4}};
}
