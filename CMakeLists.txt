cmake_minimum_required(VERSION 3.12)

project(all_cpp CXX)

# https://qiita.com/tats-u/items/ef149aee6b69407db79b
# 全てのプロジェクトにutf8のビルドoptionを追加
add_compile_options("$<$<C_COMPILER_ID:MSVC>:/source-charset:utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/source-charset:utf-8>")

add_subdirectory(01_vector_performance)
add_subdirectory(02_constructor)