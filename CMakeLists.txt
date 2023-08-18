cmake_minimum_required(VERSION 3.11)

project(scsv)

if (CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    add_library(project_warnings INTERFACE)
    include(cmake/warnings.cmake)
    set_project_warnings(project_warnings)
endif ()

if (CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    enable_testing()
    include(GoogleTest)
endif ()

include(cmake/conan.cmake)

add_library(${PROJECT_NAME} INTERFACE)
target_link_libraries(${PROJECT_NAME} INTERFACE ${CONAN_LIBS})
target_include_directories(${PROJECT_NAME} INTERFACE include)
target_compile_features(${PROJECT_NAME} INTERFACE cxx_std_20)

if (CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME OR MODERN_CMAKE_BUILD_TESTING)
    if (NOT CONAN_EXPORTED)
        add_subdirectory(tests)
    endif ()
endif ()
