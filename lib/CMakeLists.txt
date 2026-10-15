cmake_minimum_required(VERSION 3.5.1)
project(libunifireharm CXX C)

# Force C++20 or higher since the code uses standard library features
# set(CMAKE_CXX_STANDARD 20)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find the required libusb-1.0 library
find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBUSB REQUIRED IMPORTED_TARGET libusb-1.0)

set(SOURCES
    include/ButtonType.h
    include/FrameHandler.h
    include/KeyPress.h
    include/KeyPressFrame.h
    include/KeyPressType.h
    include/UnifiedReharmonizer.h
    include/PendingKeyPress.h
    include/libunifireharm.h
    src/KeyPressFrame.cpp
    src/FrameHandler.cpp
    src/UnifiedReharmonizer.cpp
)

# Define the executable target
add_library(libunifireharm ${SOURCES})

set_property(TARGET libunifireharm PROPERTY CXX_STANDARD 20)

# Include libusb headers and link the library
target_link_libraries(libunifireharm ${LIBUSB_LIBRARIES})

install(TARGETS libunifireharm DESTINATION bin)
