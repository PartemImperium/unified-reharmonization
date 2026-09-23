cmake_minimum_required(VERSION 3.5.1)
project(Sniffer CXX C)

# Force C++11 or higher since the code uses standard library features
# set(CMAKE_CXX_STANDARD 11)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find the required libusb-1.0 library
find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBUSB REQUIRED IMPORTED_TARGET libusb-1.0)

set(SOURCES
    Sniffer.cpp
)

# Define the executable target
add_executable(Sniffer ${SOURCES})

# Include libusb headers and link the library
set_property(TARGET Sniffer PROPERTY CXX_STANDARD 17)

target_link_libraries(Sniffer ${LIBUSB_LIBRARIES})

install(TARGETS Sniffer DESTINATION bin)