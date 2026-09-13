cmake_minimum_required(VERSION 3.16)
project(recipe_app VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
endif()

find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_library(recipe_app_lib
    src/model/Recipe.cpp
)
target_include_directories(recipe_app_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

add_executable(recipe_app
    src/main.cpp
    src/views/RecipeView.cpp
    src/views/RecipeView.h
    resources/recipe_app.qrc
)
target_link_libraries(recipe_app PRIVATE recipe_app_lib Qt6::Widgets)

option(BUILD_TESTING "Build tests" ON)
if(BUILD_TESTING)
    enable_testing()
    add_subdirectory(tests)
endif()
