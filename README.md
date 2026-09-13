# Recipe App

A Qt 6 desktop application for displaying recipes.

## Prerequisites

- CMake 3.16 or newer
- A C++17-compatible compiler
- Qt 6 with the Widgets component
- Internet access during the first test-enabled configure, so CMake can download GoogleTest and GoogleMock

## Build

From the project root:

```sh
cmake -S . -B build -DBUILD_TESTING=ON
cmake --build build
```

The application executable is created at `build/recipe_app`.

## Run

```sh
./build/recipe_app
```

## Test

Build the test target and run all tests with CTest:

```sh
cmake --build build --target recipe_app_tests
ctest --test-dir build --output-on-failure
```

To configure without tests:

```sh
cmake -S . -B build -DBUILD_TESTING=OFF
cmake --build build
```

Tests use GoogleTest and GoogleMock, fetched automatically by CMake when `BUILD_TESTING` is enabled.
