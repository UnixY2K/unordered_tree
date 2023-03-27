#include <catch2/catch_test_macros.hpp>
#include <unordered_tree/node.hpp>
#include <unordered_tree/node_value.hpp>

TEST_CASE("Test node behavior", "[Node]") {
	SECTION("test whether it can be reasigned") {
		Node node{"parent"};
		REQUIRE(node.is<void>());
		node = Node{"parent", Node{"child", NodeValue{}}};
		REQUIRE(node.is<Node>());
	}
}
