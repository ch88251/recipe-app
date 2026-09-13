#pragma once
#include <string>
#include <vector>

struct NutritionInfo {
    double calories = 0.0;
    double protein = 0.0;
    double carbs = 0.0;
    double fat = 0.0;
    double fiber = 0.0;
    double sugar = 0.0;
};

struct Ingredient {
    std::string name;
    double quantity = 0.0;
    std::string unit;
    NutritionInfo nutrition;
};

class Recipe {
public:
    Recipe(std::string name,
           std::string description,
           std::vector<Ingredient> ingredients,
           std::vector<std::string> directions);

    const std::string& name() const;
    const std::string& description() const;
    const std::vector<Ingredient>& ingredients() const;
    const std::vector<std::string>& directions() const;

private:
    std::string name_;
    std::string description_;
    std::vector<Ingredient> ingredients_;
    std::vector<std::string> directions_;
};