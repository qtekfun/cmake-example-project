# src/module2/CMakeLists.txt
add_library(module2 module2.cpp)

# Specify include directories for this module
target_include_directories(module2 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

