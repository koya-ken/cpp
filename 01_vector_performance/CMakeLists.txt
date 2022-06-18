cmake_minimum_required(VERSION 3.12)

project(vector_performance CXX)

file(GLOB SOURCE_LIST CONFIGURE_DEPENDS "*.cpp")

add_executable(vector_performance ${SOURCE_LIST})
target_compile_features(vector_performance PRIVATE cxx_std_17)

install(TARGETS vector_performance DESTINATION bin)