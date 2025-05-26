#include <catch2/catch_test_macros.hpp>

#include <unordered_tree/node.hpp>
#include <unordered_tree/node_value.hpp>
#include <unordered_tree/scalar_value.hpp>

TEST_CASE("Test node behavior", "[Node]") {
	SECTION("test whether it can be reasigned") {
		ouroboros::Node node;
		REQUIRE(node.is<void>());
		node = ouroboros::NodeValue{ouroboros::ScalarValue{"hello"}};
		REQUIRE(node.is<ouroboros::Node>());
	}
}
