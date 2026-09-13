#include "views/RecipeView.h"

#include <QFrame>
#include <QFont>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QListWidget>
#include <QMouseEvent>
#include <QPixmap>
#include <QPushButton>
#include <QSizePolicy>
#include <QStyle>
#include <QVBoxLayout>

namespace {
class TitleBar : public QFrame {
public:
    explicit TitleBar(QWidget* parent = nullptr) : QFrame(parent) {
        setFixedHeight(56);
        setStyleSheet("QFrame { background: #2f4858; }"
                      "QLabel { color: white; }"
                      "QPushButton { color: white; background: transparent; border: none;"
                      "font-size: 22px; padding: 4px 12px; }"
                      "QPushButton:hover { background: #406579; }");

        auto* title = new QLabel("Recipe Application", this);
        title->setAttribute(Qt::WA_TransparentForMouseEvents);
        QFont titleFont = title->font();
        titleFont.setPointSize(20);
        titleFont.setBold(true);
        title->setFont(titleFont);

        auto* closeButton = new QPushButton("X", this);
        connect(closeButton, &QPushButton::clicked, this, [this] {
            window()->close();
        });

        auto* layout = new QHBoxLayout(this);
        layout->setContentsMargins(16, 0, 4, 0);
        layout->addWidget(title);
        layout->addStretch();
        layout->addWidget(closeButton);
    }

protected:
    void mousePressEvent(QMouseEvent* event) override {
        if (event->button() == Qt::LeftButton) {
            dragOffset_ = event->globalPosition().toPoint() - window()->frameGeometry().topLeft();
            event->accept();
            return;
        }
        QFrame::mousePressEvent(event);
    }

    void mouseMoveEvent(QMouseEvent* event) override {
        if (event->buttons() & Qt::LeftButton) {
            window()->move(event->globalPosition().toPoint() - dragOffset_);
            event->accept();
            return;
        }
        QFrame::mouseMoveEvent(event);
    }

private:
    QPoint dragOffset_;
};

QFrame* createPanel(QWidget* parent) {
    auto* panel = new QFrame(parent);
    panel->setFrameShape(QFrame::StyledPanel);
    panel->setFrameShadow(QFrame::Plain);
    return panel;
}

QLabel* createPanelLabel(const QString& text, QWidget* parent) {
    auto* label = new QLabel(text, parent);
    label->setWordWrap(true);
    label->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    return label;
}
}

RecipeView::RecipeView(const Recipe& recipe, QWidget* parent) : QWidget(parent) {
    setWindowTitle("Recipe Application");
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    setFixedSize(1600, 1000);

    auto* windowLayout = new QVBoxLayout(this);
    windowLayout->setContentsMargins(0, 0, 0, 0);
    windowLayout->setSpacing(0);
    windowLayout->addWidget(new TitleBar(this));

    auto* recipeHeader = createPanel(this);
    recipeHeader->setFixedHeight(96);
    recipeHeader->setStyleSheet("QPushButton { color: white; background: #2f4858; border: none;"
                                "padding: 6px 12px; }"
                                "QPushButton:hover { background: #406579; }");

    auto* recipeHeaderLayout = new QHBoxLayout(recipeHeader);
    recipeHeaderLayout->setContentsMargins(8, 0, 8, 0);

    auto* title = new QLabel(QString::fromStdString(recipe.name()), recipeHeader);
    QFont titleFont = title->font();
    titleFont.setPointSize(titleFont.pointSize() + 16);
    titleFont.setBold(true);
    title->setFont(titleFont);
    title->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    recipeHeaderLayout->addWidget(title);
    recipeHeaderLayout->setSpacing(24);
    recipeHeaderLayout->addStretch();

    auto* addButton = new QPushButton(recipeHeader);
    addButton->setIcon(style()->standardIcon(QStyle::SP_FileDialogNewFolder));
    addButton->setIconSize(QSize(40, 40));
    addButton->setFixedSize(80, 80);
    addButton->setToolTip("Add");

    auto* searchButton = new QPushButton(recipeHeader);
    searchButton->setIcon(style()->standardIcon(QStyle::SP_FileDialogContentsView));
    searchButton->setIconSize(QSize(40, 40));
    searchButton->setFixedSize(80, 80);
    searchButton->setToolTip("Search");
    recipeHeaderLayout->addWidget(addButton);
    recipeHeaderLayout->addWidget(searchButton);

    auto* helpButton = new QPushButton(recipeHeader);
    helpButton->setIcon(style()->standardIcon(QStyle::SP_MessageBoxQuestion));
    helpButton->setIconSize(QSize(40, 40));
    helpButton->setFixedSize(80, 80);
    helpButton->setToolTip("Help");
    recipeHeaderLayout->addWidget(helpButton);

    const int imagePadding = 10;
    auto* photoPanel = createPanel(this);
    auto* photoLabel = new QLabel(photoPanel);
    const QPixmap photo(":/images/fajitas.png");
    if (!photo.isNull()) {
        photoLabel->setPixmap(photo.scaled(300, 300, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        photoLabel->setFixedSize(photoLabel->sizeHint());
    } else {
        photoLabel->setText("Photo unavailable");
    }
    auto* photoLayout = new QGridLayout(photoPanel);
    photoLayout->setContentsMargins(imagePadding, imagePadding, imagePadding, imagePadding);
    photoLayout->addWidget(photoLabel);
    photoPanel->setFixedSize(photoLabel->sizeHint() +
                             QSize(2 * (imagePadding + photoPanel->frameWidth()),
                                   2 * (imagePadding + photoPanel->frameWidth())));

    // Description panel
    auto* descriptionPanel = createPanel(this);
    auto* descriptionLabel = createPanelLabel(
        QString::fromStdString(recipe.description()), descriptionPanel);
    auto* descriptionLayout = new QGridLayout(descriptionPanel);
    QFont descriptionFont = descriptionLabel->font();
    descriptionFont.setPointSize(descriptionFont.pointSize() + 6);
    descriptionLabel->setFont(descriptionFont);
    descriptionLayout->addWidget(descriptionLabel);

    // Nutrition Information
    NutritionInfo nutrition;
    for (const Ingredient& ingredient : recipe.ingredients()) {
        nutrition.calories += ingredient.nutrition.calories;
        nutrition.protein += ingredient.nutrition.protein;
        nutrition.carbs += ingredient.nutrition.carbs;
        nutrition.fat += ingredient.nutrition.fat;
        nutrition.fiber += ingredient.nutrition.fiber;
        nutrition.sugar += ingredient.nutrition.sugar;
    }

    // Nutrition Panel
    auto* nutritionPanel = createPanel(this);
    auto* nutritionTitle = new QLabel("Nutrition Info", nutritionPanel);
    QFont nutritionTitleFont = nutritionTitle->font();
    nutritionTitleFont.setPointSize(nutritionTitleFont.pointSize() + 8);
    nutritionTitleFont.setBold(true);
    nutritionTitle->setFont(nutritionTitleFont);

    auto* nutritionLabel = createPanelLabel(
        QString("Protein: %1g, Fat: %2g, Fiber: %3g, Carbs: %4g, Sugar: %5g, Calories: %6")
            .arg(nutrition.protein, 0, 'g', 6)
            .arg(nutrition.fat, 0, 'g', 6)
            .arg(nutrition.fiber, 0, 'g', 6)
            .arg(nutrition.carbs, 0, 'g', 6)
            .arg(nutrition.sugar, 0, 'g', 6)
            .arg(nutrition.calories, 0, 'g', 6),
        nutritionPanel);
        QFont nutritionFont = nutritionLabel->font();
        nutritionFont.setPointSize(nutritionFont.pointSize() + 6);
        nutritionLabel->setFont(nutritionFont);
    nutritionLabel->setWordWrap(false);
    auto* nutritionLayout = new QVBoxLayout(nutritionPanel);
    nutritionLayout->addWidget(nutritionTitle);
    nutritionLayout->addWidget(nutritionLabel);

    auto* ingredientList = new QListWidget(this);
    QFont ingredientFont = ingredientList->font();
    ingredientFont.setPointSize(ingredientFont.pointSize() + 8);
    ingredientList->setFont(ingredientFont);

    for (const Ingredient& ingredient : recipe.ingredients()) {
        const QString quantity = QString::number(ingredient.quantity, 'g', 6);
        const QString text = QString("%1 %2 %3")
                                  .arg(quantity)
                                  .arg(QString::fromStdString(ingredient.unit))
                                  .arg(QString::fromStdString(ingredient.name));

        ingredientList->addItem(text);
    }

    auto* ingredientsPanel = createPanel(this);
    auto* ingredientsTitle = new QLabel("Ingredients", ingredientsPanel);
    QFont ingredientsTitleFont = ingredientsTitle->font();
    ingredientsTitleFont.setBold(true);
    ingredientsTitle->setFont(ingredientsTitleFont);
    auto* ingredientsLayout = new QVBoxLayout(ingredientsPanel);
    ingredientsLayout->addWidget(ingredientsTitle);
    ingredientsLayout->addWidget(ingredientList);

    auto* directionsPanel = createPanel(this);
    auto* directionsTitle = new QLabel("Directions", directionsPanel);
    QFont directionsTitleFont = directionsTitle->font();
    directionsTitleFont.setBold(true);
    directionsTitle->setFont(directionsTitleFont);
    auto* directionsList = new QListWidget(directionsPanel);
    QFont directionsFont = directionsList->font();
    directionsFont.setPointSize(directionsFont.pointSize() + 8);
    directionsList->setFont(directionsFont);
    for (std::size_t index = 0; index < recipe.directions().size(); ++index) {
        const QString step = QString("%1. %2")
                                  .arg(static_cast<int>(index + 1))
                                  .arg(QString::fromStdString(recipe.directions()[index]));
        directionsList->addItem(step);
    }
    if (recipe.directions().empty()) {
        directionsList->addItem("No directions available.");
    }
    auto* directionsLayout = new QVBoxLayout(directionsPanel);
    directionsLayout->addWidget(directionsTitle);
    directionsLayout->addWidget(directionsList);

    auto* layout = new QGridLayout;
    windowLayout->addLayout(layout);
    layout->addWidget(recipeHeader, 0, 0, 1, 2);
    layout->addWidget(photoPanel, 1, 0, 2, 1);
    layout->addWidget(descriptionPanel, 1, 1);
    layout->addWidget(nutritionPanel, 2, 1);
    layout->addWidget(ingredientsPanel, 3, 0, 1, 2);
    layout->addWidget(directionsPanel, 4, 0, 1, 2);
    const int rightPanelSpacing = layout->verticalSpacing();
    const int rightPanelHeight = (photoPanel->height() - rightPanelSpacing) / 2;
    descriptionPanel->setFixedHeight(rightPanelHeight);
    nutritionPanel->setFixedHeight(photoPanel->height() - rightPanelSpacing - rightPanelHeight);
    layout->setRowStretch(3, 1);
    layout->setRowStretch(4, 1);
}
