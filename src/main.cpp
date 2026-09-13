#include <QApplication>

#include "model/Recipe.h"
#include "views/RecipeView.h"

int main(int argc, char** argv) {
    QApplication app(argc, argv);

    Recipe fajitas(
        "Fajitas",
        "Tender chicken and vegetables seasoned with fajita spices and served in warm tortillas.",
        {
            {"Chicken", 1.0, "lb"},
            {"Bell Peppers", 2.0, "each"},
            {"Onion", 1.0, "each"},
            {"Fajita Seasoning", 2.0, "tbsp"},
            {"Tortillas", 8.0, "each"},
        },
        {
            "Slice the chicken, bell peppers, and onion.",
            "Cook the chicken in a hot skillet until browned and cooked through.",
            "Add the vegetables and fajita seasoning, then cook until tender.",
            "Serve the filling in warm tortillas.",
        });

    RecipeView view(fajitas);
    view.show();

    return app.exec();
}
