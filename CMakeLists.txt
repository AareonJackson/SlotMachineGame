# Root CMakeLists.txt for Slot-Machine project
cmake_minimum_required(VERSION 3.15)
project(Slot-Machine VERSION 0.1.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Options
option(BUILD_TESTS "Build test programs" ON)
option(BUILD_DOCS "Build documentation" OFF)

# Output directories
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Include custom CMake modules
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# Check if SFML exists in the specified external directory
set(SFML_LOCAL_PATH "${CMAKE_CURRENT_SOURCE_DIR}/external/sfml")
if(EXISTS "${SFML_LOCAL_PATH}")
    message(STATUS "Using local SFML from ${SFML_LOCAL_PATH}")

    # Option 1: If SFML is already built and just needs to be included
    if(EXISTS "${SFML_LOCAL_PATH}/lib/cmake/SFML/SFMLConfig.cmake")
        set(SFML_DIR "${SFML_LOCAL_PATH}/lib/cmake/SFML")
        find_package(SFML 2.5 COMPONENTS graphics window system audio REQUIRED)
        # Option 2: If SFML is provided as source and needs to be built
    elseif(EXISTS "${SFML_LOCAL_PATH}/CMakeLists.txt")
        # Add SFML as a subdirectory to build it as part of this project
        # Disable SFML examples and tests to speed up the build
        set(SFML_BUILD_EXAMPLES OFF CACHE BOOL "Build the SFML examples" FORCE)
        set(SFML_BUILD_DOC OFF CACHE BOOL "Build the SFML documentation" FORCE)
        set(SFML_BUILD_NETWORK OFF CACHE BOOL "Build the SFML network module" FORCE)
        set(BUILD_SHARED_LIBS ON CACHE BOOL "Build shared libraries" FORCE)

        add_subdirectory(${SFML_LOCAL_PATH} sfml_build)
    else()
        message(FATAL_ERROR "SFML directory exists but doesn't contain expected files. Please ensure SFML is properly placed in ${SFML_LOCAL_PATH}")
    endif()
else()
    message(STATUS "Local SFML not found at ${SFML_LOCAL_PATH}, downloading it...")

    # Use FetchContent to download SFML
    include(FetchContent)
    FetchContent_Declare(
            SFML
            GIT_REPOSITORY https://github.com/SFML/SFML.git
            GIT_TAG 2.5.1
    )

    # Configure SFML build options
    set(SFML_BUILD_EXAMPLES OFF CACHE BOOL "Build the SFML examples" FORCE)
    set(SFML_BUILD_DOC OFF CACHE BOOL "Build the SFML documentation" FORCE)
    set(SFML_BUILD_NETWORK OFF CACHE BOOL "Build the SFML network module" FORCE)
    set(BUILD_SHARED_LIBS ON CACHE BOOL "Build shared libraries" FORCE)

    FetchContent_MakeAvailable(SFML)
endif()

# Common compiler warnings
if(MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Include directories for the entire project
include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Define source files
set(SOURCES
        src/main.cpp
        src/core/engine.cpp
        src/core/rng.cpp
        src/core/payout.cpp
        src/ui/game_window.cpp
        src/ui/button.cpp
        src/ui/reel_view.cpp
        src/audio/sound_manager.cpp
        src/config/config_manager.cpp
)

# Define header files
set(HEADERS
        include/core/engine.h
        include/core/rng.h
        include/core/payout.h
        include/ui/game_window.h
        include/ui/button.h
        include/ui/reel_view.h
        include/audio/sound_manager.h
        include/config/config_manager.h
)

# Main executable
add_executable(SlotMachine ${SOURCES} ${HEADERS})

# Link libraries
target_link_libraries(SlotMachine
        PRIVATE
        sfml-graphics
        sfml-window
        sfml-system
        sfml-audio
)

# Include path - more specific way than global include_directories
target_include_directories(SlotMachine
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Copy assets to build directory
add_custom_command(TARGET SlotMachine POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/assets $<TARGET_FILE_DIR:SlotMachine>/assets
)

# Generate compile_commands.json for tools like clang-tidy
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Testing
if(BUILD_TESTS)
    enable_testing()
    # Uncomment the line below when you have a tests directory with CMakeLists.txt
    # add_subdirectory(tests)
endif()

# Documentation
if(BUILD_DOCS)
    find_package(Doxygen)
    if(DOXYGEN_FOUND)
        # Uncomment the line below when you have a docs directory with CMakeLists.txt
        # add_subdirectory(docs)
    else()
        message(STATUS "Doxygen not found, documentation will not be built")
    endif()
endif()

# Installation rules
install(TARGETS SlotMachine
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
)
install(DIRECTORY assets/ DESTINATION bin/assets)

# Print configuration summary
message(STATUS "CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}")
message(STATUS "BUILD_TESTS: ${BUILD_TESTS}")
message(STATUS "BUILD_DOCS: ${BUILD_DOCS}")