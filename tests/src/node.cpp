#include <catch2/catch_test_macros.hpp>
#include <unordered_tree/node.hpp>
#include <unordered_tree/node_value.hpp>

TEST_CASE("Test node behavior", "[Node]") {
	SECTION("test whether it can be reasigned") {
		ouroboros::Node node{"parent"};
		REQUIRE(node.is<void>());
		node = ouroboros::Node{"parent", ouroboros::Node{"child", ouroboros::NodeValue{}}};
		REQUIRE(node.is<ouroboros::Node>());
	}
}
