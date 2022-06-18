cmake_minimum_required(VERSION 3.12)

project(constructor CXX)

file(GLOB SOURCE_LIST CONFIGURE_DEPENDS "*.cpp")

add_executable(constructor ${SOURCE_LIST})
target_compile_features(constructor PRIVATE cxx_std_17)

install(TARGETS constructor DESTINATION bin)