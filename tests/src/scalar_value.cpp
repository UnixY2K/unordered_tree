#include <catch2/catch_test_macros.hpp>
#include <unordered_tree/scalar_value.hpp>
#include <variant>

TEST_CASE("Test scalar value behavior", "[ScalarValue]") {
	SECTION("check wheter it can be reasigned") {
		ScalarValue sv{};
		REQUIRE(sv.is<std::monostate>());
		sv = {2};
		REQUIRE(sv.is<int>());
		sv = {2.2f};
		REQUIRE(sv.is<float>());
	}
}
