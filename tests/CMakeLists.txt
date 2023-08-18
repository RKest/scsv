add_executable("${PROJECT_NAME}_test" Test.cpp)
target_link_libraries("${PROJECT_NAME}_test" PRIVATE ${PROJECT_NAME})
gtest_discover_tests("${PROJECT_NAME}_test")