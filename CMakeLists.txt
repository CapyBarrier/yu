cmake_minimum_required(VERSION 4.3.0)
project(yu CXX)

add_library(yu INTERFACE)

target_include_directories(yu
    INTERFACE
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

target_compile_features(yu
    INTERFACE
        cxx_std_23
)

target_compile_options(yu
    INTERFACE
        -Wall
        -Wextra
)

enable_testing()

add_subdirectory(docs)
add_subdirectory(tests)