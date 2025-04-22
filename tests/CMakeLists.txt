# Tests CMakeLists.txt
find_package(GTest REQUIRED)
include(GoogleTest)

add_subdirectory(unit)
add_subdirectory(integration)