#pragma once
#include <QWidget>

#include "model/Recipe.h"

class RecipeView : public QWidget {
    Q_OBJECT

public:
    explicit RecipeView(const Recipe& recipe, QWidget* parent = nullptr);
};
