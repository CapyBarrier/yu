cmake_minimum_required(VERSION 3.23)

project(yu LANGUAGES CXX)

# selectだけ追加
add_subdirectory(libs/select)

# テスト実行ファイル
add_executable(yu_select_test
    tests/select_test.cpp
)

target_link_libraries(yu_select_test
    PRIVATE yu.select
)