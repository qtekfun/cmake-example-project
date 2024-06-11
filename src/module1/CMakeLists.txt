# src/module1/CMakeLists.txt
add_library(module1 module1.cpp)

# Specify include directories for this module
target_include_directories(module1 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Link module2 to module1
target_link_libraries(module1 PRIVATE module2)

