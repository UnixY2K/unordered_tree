#include <algorithm>
#include <string>
#include <unordered_tree/node.hpp>

void Node::set_id(std::string const &new_id) { id = new_id; }
void Node::set_id(std::string &&new_id) noexcept { id = std::move(new_id); }
std::string_view Node::get_id() const { return id; }
