# src/client/CMakeLists.txt

# Create a library for the client module
add_library(client STATIC
    RateLimiter.cpp
    ClientRequestHandler.cpp
)

# Specify include directories for the client module
target_include_directories(client PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
