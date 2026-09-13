#include <cassert>
#include <iostream>

#include "model/Recipe.h"

int main() {
    Recipe recipe("Toast",
                  "Crispy bread with a golden crust.",
                  {{"Bread", 2.0, "slices"}},
                  {"Toast the bread.", "Serve while warm."});

    assert(recipe.name() == "Toast");
    assert(recipe.description() == "Crispy bread with a golden crust.");
    assert(recipe.ingredients().size() == 1);
    assert(recipe.ingredients()[0].name == "Bread");
    assert(recipe.directions().size() == 2);
    assert(recipe.directions()[0] == "Toast the bread.");
    assert(recipe.directions()[1] == "Serve while warm.");

    std::cout << "All tests passed.\n";
    return 0;
}
