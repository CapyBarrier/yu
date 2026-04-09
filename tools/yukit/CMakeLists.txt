cmake_minimum_required(VERSION 3.20)

project(yukit LANGUAGES CXX)

add_executable(yukit
    src/main.cpp
    src/replace_all_namespace_quarifier.cpp
    src/get_root.cpp
    src/index_cmd.cpp
    src/status_cmd.cpp
    src/new_cmd.cpp
)

target_compile_features(yukit PRIVATE cxx_std_23)