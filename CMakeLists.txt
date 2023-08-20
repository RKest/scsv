cmake_minimum_required(VERSION 3.11)

project(
        scsv
        VERSION 0.1.0
        DESCRIPTION "CSV to static data types parser"
        HOMEPAGE_URL ""
)

if (CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    add_library(project_warnings INTERFACE)
    include(cmake/warnings.cmake)
    set_project_warnings(project_warnings)
endif ()

include(cmake/conan.cmake)

add_library(${PROJECT_NAME} INTERFACE include/scsv/detail/mmap_reading.hpp)
target_link_libraries(${PROJECT_NAME} INTERFACE ${CONAN_LIBS})
target_include_directories(${PROJECT_NAME} INTERFACE include)
target_compile_features(${PROJECT_NAME} INTERFACE cxx_std_20)

if (CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME OR MODERN_CMAKE_BUILD_TESTING)
    if (NOT CONAN_EXPORTED)
        enable_testing()
        include(GoogleTest)
        add_subdirectory(tests)
    endif ()
endif ()
