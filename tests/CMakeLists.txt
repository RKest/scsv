add_executable("${PROJECT_NAME}_test" Test.cpp Benchmark.cpp IntegrationTest.cpp)
message(STATUS "CONAN_LIBS: ${CONAN_LIBS}")
target_link_libraries("${PROJECT_NAME}_test" PUBLIC ${PROJECT_NAME} ${CONAN_LIBS})
gtest_discover_tests("${PROJECT_NAME}_test" WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})