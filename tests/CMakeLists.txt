include(GoogleTest)

add_executable(recipe_app_tests test_recipe.cpp)
target_link_libraries(recipe_app_tests
	PRIVATE
		recipe_app_lib
		GTest::gtest_main
		GTest::gmock
)

gtest_discover_tests(recipe_app_tests)
