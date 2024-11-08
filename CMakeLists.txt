cmake_minimum_required(VERSION 3.10)

# Project name and version
project(LoadBalancerSystem VERSION 1.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include FetchContent for external dependencies
include(FetchContent)

# Google Test setup
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/release-1.12.1.zip
)
FetchContent_MakeAvailable(googletest)

# Add subdirectories for different components of the project
add_subdirectory(client)
add_subdirectory(loadbalancer)
add_subdirectory(workerPool)
add_subdirectory(processing)
add_subdirectory(response)
add_subdirectory(monitoring)
add_subdirectory(utils)

# Find and enable Threads
find_package(Threads REQUIRED)

# Add the main executable
add_executable(LoadBalancerSystem src/main.cpp)

# Link all module libraries and Threads to the main executable
target_link_libraries(LoadBalancerSystem PRIVATE
    client
    loadbalancer
    workerPool
    processing
    response
    monitoring
    utils
    Threads::Threads
)

# Add the test executable (assuming you have a test file in src/tests.cpp)
add_executable(LoadBalancerSystemTests src/tests.cpp)

# Link GoogleTest and main system executable to the test executable
target_link_libraries(LoadBalancerSystemTests PRIVATE gtest_main LoadBalancerSystem)

# Enable testing and add test executable
enable_testing()
add_test(NAME LoadBalancerSystemTests COMMAND LoadBalancerSystemTests)
