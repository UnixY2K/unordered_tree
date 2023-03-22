#pragma once
#include <string>
#include <unordered_tree/node_value.hpp>
#include <variant>
#include <vector>

class Node {
	using node_val_t = std::variant<NodeValue, std::vector<NodeValue>>;
	std::string id;
	// a node can contain 0(monostate/void) or more elements, if the list of
	// elements is 0 it is empty
	node_val_t value{std::monostate{}};

  public:
	Node() = default;
	Node(Node const &other) noexcept = default;
	Node(Node &&other) = default;

	void set_id(std::string const &new_id);
	void set_id(std::string &&new_id) noexcept;
	std::string_view get_id() const;

	Node &operator=(Node const &other) noexcept = default;
	Node &operator=(Node &&other) = default;
};
