include(FetchContent)

FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.1.0
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

add_library(Comppose_SFML STATIC Comppose.cpp)
target_link_libraries(Comppose_SFML Comppose)
add_library(Comppose::SFML ALIAS Comppose_SFML)