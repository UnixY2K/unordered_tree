#include <catch2/catch_test_macros.hpp>
#include <unordered_tree/node.hpp>
#include <unordered_tree/node_value.hpp>

TEST_CASE("Test node value behavior", "[NodeValue]") {
	SECTION("test wheter it can be reasigned") {
		NodeValue nv{};
		REQUIRE(nv.is<void>());
		nv = Node{};
		REQUIRE(nv.is<Node>());
	}
}
