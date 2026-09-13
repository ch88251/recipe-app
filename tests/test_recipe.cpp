#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "model/Recipe.h"

TEST(RecipeTest, StoresRecipeDetailsAndDirections) {
    Recipe recipe("Toast",
                  "Crispy bread with a golden crust.",
                  {{"Bread", 2.0, "slices"}},
                  {"Toast the bread.", "Serve while warm."});

    EXPECT_EQ(recipe.name(), "Toast");
    EXPECT_EQ(recipe.description(), "Crispy bread with a golden crust.");
    ASSERT_EQ(recipe.ingredients().size(), 1);
    EXPECT_EQ(recipe.ingredients()[0].name, "Bread");
    ASSERT_EQ(recipe.directions().size(), 2);
    EXPECT_EQ(recipe.directions()[0], "Toast the bread.");
    EXPECT_EQ(recipe.directions()[1], "Serve while warm.");
}
