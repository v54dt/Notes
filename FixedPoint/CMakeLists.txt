cmake_minimum_required(VERSION 3.10)
project(FixedPointLibrary VERSION 1.0.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find or fetch the fpm library
# Option 1: If fpm is installed system-wide
# find_package(fpm REQUIRED)

# Option 2: Use FetchContent to download fpm
include(FetchContent)
FetchContent_Declare(
    fpm
    GIT_REPOSITORY https://github.com/MikeLankamp/fpm.git
    GIT_TAG        master
)
FetchContent_MakeAvailable(fpm)

# Create the library
add_library(fixedpoint STATIC
    fixedpoint.cpp
    fixedpoint.h
)

# Set include directories
target_include_directories(fixedpoint PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include>
)

# Link fpm library
target_link_libraries(fixedpoint PUBLIC fpm)

# Create the example executable
add_executable(example example.cpp)
target_link_libraries(example PRIVATE fixedpoint)

# Enable testing
enable_testing()
add_test(NAME ExampleTest COMMAND example)

# Installation rules
install(TARGETS fixedpoint
    EXPORT FixedPointTargets
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
)

install(FILES fixedpoint.h DESTINATION include)

# Export targets
install(EXPORT FixedPointTargets
    FILE FixedPointTargets.cmake
    NAMESPACE FixedPoint::
    DESTINATION lib/cmake/FixedPoint
)

# Create package configuration file
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/FixedPointConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY AnyNewerVersion
)

configure_file(cmake/FixedPointConfig.cmake.in
    "${CMAKE_CURRENT_BINARY_DIR}/FixedPointConfig.cmake"
    @ONLY
)

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/FixedPointConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/FixedPointConfigVersion.cmake"
    DESTINATION lib/cmake/FixedPoint
)
