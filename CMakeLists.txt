cmake_minimum_required(VERSION 3.10.0)
project(Comppose VERSION 0.1.0 LANGUAGES C CXX)

add_library(Comppose INTERFACE)
target_include_directories(Comppose INTERFACE include)

subdirs(
    impl/sfml
    assets
)

add_executable(demo src/main.cpp)
target_link_libraries(demo PUBLIC Comppose Comppose::SFML)