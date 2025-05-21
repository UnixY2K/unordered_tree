#include <catch2/catch_test_macros.hpp>
#include <unordered_tree/node.hpp>
#include <unordered_tree/node_value.hpp>

TEST_CASE("Test node value behavior", "[NodeValue]") {
	SECTION("test whether it can be reasigned") {
		ouroboros::NodeValue nv{};
		REQUIRE(nv.is<void>());
		nv = ouroboros::Node{};
		REQUIRE(nv.is<ouroboros::Node>());
	}
}
