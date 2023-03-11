#include <format>
#include <iostream>
#include <unordered_tree/node.hpp>

int main() {
	NodeValue value{Node{}};
	bool is_scalar = value.is<ScalarValue>(); // returns true
	bool is_node = value.is<Node>();          // returns false
	bool is_int = value.is<int>();            // returns true
	std::cout << std::format("is_scalar: {}\n", is_scalar);
	std::cout << std::format("is_node: {}\n", is_node);
	std::cout << std::format("is_int: {}\n", is_int);
}
