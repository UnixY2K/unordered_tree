#include <format>
#include <iostream>
#include <unordered_tree/node.hpp>
#include <variant>

std::string get_type(NodeValue value) {
	std::string type = "unkown";
	if (value.is<int>()) {
		type = "int";
	} else if (value.is<bool>()) {
		type = "bool";
	} else if (value.is<char>()) {
		type = "char";
	} else if (value.is<float>()) {
		type = "float";
	} else if (value.is<double>()) {
		type = "double";
	} else if (value.is<std::string>()) {
		type = "string";
	} else if (value.is<std::monostate>()) {
		type = "None";
	}
	return type;
}

int main() {
	NodeValue value{};
	bool is_scalar = value.is<ScalarValue>(); // returns true
	bool is_node = value.is<Node>();          // returns false
	std::string type = get_type(value);
	std::cout << std::format("is_scalar: {}\n", is_scalar);
	std::cout << std::format("is_node  : {}\n", is_node);
	std::cout << std::format("type     : {}\n", type);
}
