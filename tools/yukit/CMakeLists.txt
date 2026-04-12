cmake_minimum_required(VERSION 4.2.0)

project(yukit LANGUAGES CXX)

# ---- core library ----
add_library(yukit_core)

target_sources(yukit_core
    PRIVATE
        src/yukit/cmd/index_cmd.cpp
        src/yukit/cmd/status_cmd.cpp
        src/yukit/cmd/new_cmd.cpp
        src/yukit/cmd/docs_cmd.cpp
        src/yukit/cmd/docs/pages_cmd.cpp
        src/yukit/cmd/docs/serve_cmd.cpp

        src/yukit/util/get_root.cpp
        src/yukit/util/replace_ns_qualifier.cpp
)

target_include_directories(yukit_core
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(yukit_core PUBLIC cxx_std_23)

# ---- executable ----
add_executable(yukit
    src/yukit/main.cpp
)

target_link_libraries(yukit
    PRIVATE yukit_core
)

# ---- install ----
install(TARGETS yukit
    RUNTIME DESTINATION bin
)