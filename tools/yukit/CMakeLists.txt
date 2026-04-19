cmake_minimum_required(VERSION 4.2.0)

project(yukit LANGUAGES CXX)

# ---- executable ----
add_executable(yukit)

target_sources(yukit
    PRIVATE
        src/yukit/main.cpp

        src/yukit/cmd/create.cpp
        src/yukit/cmd/create_alias.cpp
        src/yukit/cmd/make_index.cpp
        src/yukit/cmd/ref.cpp
        src/yukit/cmd/status.cpp
        src/yukit/cmd/reference/make_template.cpp
        src/yukit/cmd/reference/serve.cpp
        src/yukit/cmd/reference/pages.cpp

        src/yukit/util/entity_exists.cpp
        src/yukit/util/entity_path.cpp
        src/yukit/util/get_root.cpp
        src/yukit/util/sublib_exists.cpp
        src/yukit/util/replace_ns_qualifier.cpp
        src/yukit/util/valid_entity_name.cpp
)

target_include_directories(yukit
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(yukit
    PRIVATE cxx_std_23
)

# ---- install ----
install(TARGETS yukit
    RUNTIME DESTINATION bin
)