add_library(yu_tuples
    tuples.cpp
)

target_include_directories(yu_tuples
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include
)

add_library(Yu.tuples ALIAS yu_tuples)