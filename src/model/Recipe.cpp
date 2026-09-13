#include "model/Recipe.h"

#include <utility>

Recipe::Recipe(std::string name,
               std::string description,
               std::vector<Ingredient> ingredients,
               std::vector<std::string> directions)
    : name_(std::move(name)),
      description_(std::move(description)),
      ingredients_(std::move(ingredients)),
      directions_(std::move(directions)) {}

const std::string& Recipe::name() const { return name_; }

const std::string& Recipe::description() const { return description_; }

const std::vector<Ingredient>& Recipe::ingredients() const { return ingredients_; }

const std::vector<std::string>& Recipe::directions() const { return directions_; }
