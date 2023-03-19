#pragma once
#include <unordered_tree/node_value.hpp>

class Node {
  public:
	Node() = default;
	Node(Node const &other) noexcept = default;
	Node(Node &&other) = default;
	Node &operator=(Node const &other) noexcept = default;
	Node &operator=(Node &&other) = default;
};
