cmake_minimum_required(VERSION 3.20)

project(CircleSphereSampling LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SFML_DIR "C:/SFML-2.6.2/lib/cmake/SFML")

find_package(SFML 2.6 COMPONENTS graphics window system REQUIRED)

add_executable(app
    Main.cpp
    Sampler.cpp
    Projection.cpp
    SphereRenderer.cpp
)

target_link_libraries(app
    PRIVATE
    sfml-graphics
    sfml-window
    sfml-system
)