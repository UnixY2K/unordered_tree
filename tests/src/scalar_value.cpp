#include <catch2/catch_test_macros.hpp>
#include <unordered_tree/scalar_value.hpp>

TEST_CASE("Test scalar value behavior", "[ScalarValue]") {
	SECTION("check whether it can be reasigned") {
		ouroboros::ScalarValue sv{};
		REQUIRE(sv.is<void>());
		sv = 2;
		REQUIRE(sv.is<int>());
		sv = 2.2f;
		REQUIRE(sv.is<float>());
	}
	SECTION("test default value behavior") {
		ouroboros::ScalarValue sv{};
		REQUIRE(sv.as<int>().value_or(-1) == -1);
	}
}
