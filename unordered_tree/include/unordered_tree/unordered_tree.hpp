#pragma once
#include <initializer_list>
#include <optional>
#include <string>
#include <unordered_map>
#include <utility>
#include <variant>
#include <vector>

namespace ouroboros {
template <typename T> class unordered_tree {
	// has a key and can contain a T or a unordered_map<std::string, Node,
  public:
	class Node {
		using node_value_t =
		    std::variant<std::monostate, std::unordered_map<std::string, Node>,
		                 T>;
		node_value_t value;

	  public:
		Node() = default;
		Node(node_value_t value) : value(value) {}
		Node(std::initializer_list<std::pair<std::string, Node>> nodes) {
			value = std::unordered_map<std::string, Node>(nodes);
		}
		// initializer list for vector<T>
		Node(std::initializer_list<T> v_values) {
			value = std::vector<T>(v_values);

		}

		const node_value_t &get_value() const { return value; }
	};
	unordered_tree() = default;
	unordered_tree(Node node) : root(node) {}
	unordered_tree(std::initializer_list<Node> nodes) : root(nodes) {}

	const Node &get_root() const { return root; }

  private:
	Node root;
};
} // namespace ouroboros
