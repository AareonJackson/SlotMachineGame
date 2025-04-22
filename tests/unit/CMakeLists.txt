# Unit tests CMakeLists.txt
set(UNIT_TEST_SOURCES
        core/rng_test.cpp
        core/payout_test.cpp
        # Add other unit tests here
)

add_executable(unit_tests ${UNIT_TEST_SOURCES})
target_link_libraries(unit_tests
        PRIVATE
        GTest::GTest
        GTest::Main
        # Link to your project libraries
)

gtest_discover_tests(unit_tests)