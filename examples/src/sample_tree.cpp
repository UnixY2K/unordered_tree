#include <format>
#include <iostream>

#include <unordered_tree/node.hpp>
#include <unordered_tree/node_value.hpp>

int main() {
	ouroboros::NodeValue value{1};
	value = ouroboros::Node{};
	value = ouroboros::NodeValue{};
	bool is_scalar = value.is<ouroboros::ScalarValue>(); // returns true
	bool is_node = value.is<ouroboros::Node>();          // returns false
	std::string_view type = value.get_type();
	std::cout << std::format("is_scalar: {}\n", is_scalar);
	std::cout << std::format("is_node  : {}\n", is_node);
	std::cout << std::format("type     : {}\n", type);
}
