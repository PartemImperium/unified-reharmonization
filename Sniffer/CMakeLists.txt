cmake_minimum_required(VERSION 3.5.1)
project(Sniffer CXX C)

# Force C++20 or higher since the code uses standard library features
# set(CMAKE_CXX_STANDARD 20)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES
    Sniffer.cpp
)

# Define the executable target
add_executable(Sniffer ${SOURCES})

set_property(TARGET Sniffer PROPERTY CXX_STANDARD 20)

target_link_libraries(Sniffer "libunifireharm")

install(TARGETS Sniffer DESTINATION bin)
