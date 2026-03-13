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

# ビルド後に実行（失敗したらビルド失敗）
add_custom_command(
    TARGET yu_select_test
    POST_BUILD
    COMMAND $<TARGET_FILE:yu_select_test>
)