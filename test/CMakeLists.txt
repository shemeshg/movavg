enable_testing()
find_package(GTest REQUIRED)
include(GoogleTest)

add_executable(tests movavg_test.cpp )

TARGET_LINK_LIBRARIES(tests
    libmovavg
)


target_link_libraries(tests GTest::GTest GTest::Main)
gtest_discover_tests(tests)